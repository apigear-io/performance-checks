
import os.path
import sys
from subprocess import Popen, TimeoutExpired
import subprocess
from time import sleep
import re

TEST_TIME_SEARCH_TEXT = "Time measured" 
CLIENT_NUMBER_SEARCH_TEXT = "Objects number:"
EXECUTION_NUMBER_SEARCH_TEXT = "Function execution number for each object:"
SHELL = "SHELL"


#requires CPP_BUILD and QT_BUILD to point to binaries
class scenario:
    def __init__(self, relative_file_path, tech_mapping):

        self.servers = []
        self.clients = []
        if not os.path.isfile(relative_file_path):
            print("Input file doesn't exist")
            return;
        input_file = open(relative_file_path,'r')
        line_list = input_file.readlines()
        readingServers = False;
        readingClients = False;
        for line in line_list:
            line = line.lstrip()
            if not line:
                continue
            if line.startswith('servers:'):
                readingServers = True
                readingClients = False
            elif line.startswith('clients:'):
                readingServers = False
                readingClients = True
            elif  readingServers:
                element = setPathsAndFormat(line, tech_mapping)
                self.servers.append(element)
            elif  readingClients:
                element = setPathsAndFormat(line, tech_mapping)
                self.clients.append(element)

def setPathsAndFormat(line, tech_mapping):
    element = line.rstrip('\n');
    if "cpp" in tech_mapping.keys() and element.find("CPP_BUILD") != -1:
        element = element.replace("CPP_BUILD", tech_mapping["cpp"])
    elif "qt" in tech_mapping.keys() and element.find("QT_BUILD") != -1:
        element = element.replace("QT_BUILD", tech_mapping["qt"])
    elif "unreal" in tech_mapping.keys() and element.find("UNREAL_DIR") != -1:
        element = element.replace("UNREAL_DIR",tech_mapping["unreal"])
    elif "py" in tech_mapping.keys() and element.find("PY_DIR") != -1:
        element = element.replace("PY_DIR", tech_mapping["py"])
    return element;

#if file with given path doesnt exist it tries to remove the .exe postfix
def removePostfixIfNoOriginalFile(file_path):
    if file_path.endswith('.exe') and not os.path.isfile(file_path):
        file_path = file_path.rstrip('.exe')
    return file_path

#splits with space, avoiding spaces that are in between "" characters    
def splitClientAndArguments(client_line):
    return re.split(r'\s+(?=[^"]*(?:"[^"]*"[^"]*)*$)', client_line)  

# assumes the client file is one, which contains one of given paths to binaries
def getFileFromClientLine(words, paths):
    for word in words:
        for path in paths:
            path_index = word.find(path)
            if path_index != -1:
                return word
    print("client not found in a command")
    return ""

def prepareClientProcess(client_line, paths):
    words = splitClientAndArguments(client_line)
    clientFile = getFileFromClientLine(words, paths).lstrip("\"").rstrip("\"")
    clientFileNew = removePostfixIfNoOriginalFile(clientFile)
    if not os.path.isfile(clientFileNew):
        return []
    elif (clientFileNew != clientFile):
        words = [w.replace(clientFile, clientFileNew) for w in words]
        clientFile = clientFileNew
    # if execute as shell command it is one line, for unreal some arguments were skipped otherwise
    if len(words)>0 and words[0] == SHELL:
        words.pop(0)
        words = [SHELL, (' '.join(words))]
    return words



def main():
    
    scenarioPath =""    
    args = sys.argv[1:]
    if len(args) > 0:
        scenarioPath = args[0]
    else:
        print("no scenrio to run")
        return -1
    bin_paths, tech_mapping = getPathsFromArgumets(args)

    current_scenario = scenario(scenarioPath, tech_mapping);

    print(current_scenario.servers)
    print(current_scenario.clients)
    firstLine = "scenario: " + scenarioPath
    linesToWriteResult = [  firstLine ]
    linesToWriteCsv = [  firstLine ]
    linesToWriteCsv.append(get_csv_header())
    for client in current_scenario.clients:
        client_args = prepareClientProcess(client, bin_paths);
        if len(client_args) == 0:
            print("File doesn't exist: " + client)
            return 1
        for server in current_scenario.servers:
            try:
                server_process = None
                client_process = None
                isServerShellCommand = False
                if server.strip().startswith(SHELL):
                    isServerShellCommand = True      
                    server = server[len(SHELL):len(server)].lstrip()
                    print(server)
                server = removePostfixIfNoOriginalFile(server)
                if isServerShellCommand:
                    server_process = subprocess.Popen(server, shell=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
                else:
                    if not os.path.isfile(server):
                        print("File doesn't exist: " + server)
                        return 1
                    server_process = subprocess.Popen(server, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)  
                sleep(3)
                if len(client_args) == 0:
                    if server_process != None:
                        server_process.kill()
                    print("client not found in line")
                    print(client)
                    return 1
                if client_args[0].startswith(SHELL):
                    client_process = subprocess.Popen(client_args[1], shell=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
                else:
                    client_process = subprocess.Popen(client_args, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
                try:
                    client_process.wait(150)
                except subprocess.TimeoutExpired:
                    server_process.kill()
                    client_process.kill()
                    print("Timeout for pair: ")
                    print(client)
                    print(client_process.communicate()[0].decode)
                    print(server)
                    print(server_process.communicate()[0].decode)
                    return 1

                sleep(1)
                if server_process.poll == None:
                    server_process.kill()
            except Exception as e:
                if server_process != None:
                    server_process.kill()
                if client_process != None:
                    client_process.kill()
                raise

            if server_process != None:
                server_process.kill()
            else:
                server_outcome_lines = unify_delimeters_and_split(server_process.communicate()[0].decode())
                if (len(server_outcome_lines[0]) == 0):
                    print("someting went wrong when running " + server + " check if your exe can be run")
            client_outcome_lines = unify_delimeters_and_split(client_process.communicate()[0].decode())
            if (len(client_outcome_lines[0]) == 0):
                print("someting went wrong when running " + client + ", check if your exe can be run")
                if client_process != None:
                    client_process.kill()
                continue
            test_info = prepareTestInfo(client_outcome_lines, server, client, tech_mapping)
            formated_line = format_for_output(test_info)
            print(formated_line)
            linesToWriteResult.append(formated_line)
            linesToWriteCsv.append(format_to_csv(test_info))
            sleep(5)
    scenarioPath = scenarioPath.split("/")
    reportfolderName = "reports"

    if not os.path.exists(reportfolderName):
        os.makedirs(reportfolderName)

    resultFileName = "report_" +  scenarioPath[len(scenarioPath) -1]
    report_file = open(reportfolderName +"/"+resultFileName,'w')
    report_file.writelines(line + '\n' for line in linesToWriteResult)
    csv_report = open(reportfolderName +"/"+"csv_"+resultFileName,'w')
    csv_report.writelines(line + '\n' for line in linesToWriteCsv)
    return 0


def getPathsFromArgumets(args):

    bin_paths =[]
    tech_mapping = {}

    if len(args) > 1:
        cpp_build_path = args[1]
        if (len(cpp_build_path.strip()) != 0 ):
            bin_paths.append(cpp_build_path)
            tech_mapping["cpp"] = cpp_build_path
    if len(args) > 2:
        qt_build_path = args[2]
        if (len(qt_build_path.strip()) != 0 ):
            bin_paths.append(qt_build_path)
            tech_mapping["qt"] = qt_build_path
    if len(args) > 3:
        unreal_test_dir = args[3]
        if (len(unreal_test_dir.strip()) != 0 ):
            bin_paths.append(unreal_test_dir)
            tech_mapping["unreal"] = unreal_test_dir
    if len(args) > 4:
        python_files_dir = args[4]
        if (len(python_files_dir.strip()) != 0 ):
            bin_paths.append(python_files_dir)
            tech_mapping["py"] = python_files_dir
    
    return bin_paths, tech_mapping

# On Linux delimeter is only \n, replacing \r\n with \n makes split work on Linux and Windows platform
def unify_delimeters_and_split(lines):
    return lines.replace('\r\n', '\n').split('\n')

def getInfoFromOutput(lines, search_text):
    for line in lines:
        if (line.find(search_text) != -1):
            outcome = line.split(':')
            return outcome[1]
    return "0"

def getInfoFromOutputTimeDuration(lines, search_text):
    for line in lines:
        if (line.find(search_text) != -1):
            outcome = line.split(':')
            time = outcome[1]
            indexStart = outcome[0].find("[")
            indexStop = outcome[0].find("]")
            unit = "[?]"
            if (indexStop != -1 and indexStart != -1 and indexStart<indexStop):
                unit = outcome[0][indexStart:indexStop+1]
            return unit, time.strip()
    return "?" ,"?"

def getLatencies(lines):
    for line in lines:
        if line.startswith("Latency"):
            outcome = line.split(' ')
            if len(outcome) > 6:
                outcome = list(filter(None, outcome))
                return True, outcome[2], outcome[4], outcome[6],
    return False, -1, -1, -1 

def format_for_output(test_info):
    output =   "client " + test_info["client"] 
    output+= " server " + test_info["server"]
    output+= " requests number " + str(test_info["requests"])
    output+= " total time"+ test_info["total time unit"]  +" "+  str(test_info["total time"])
    #output+= " queries per ms " + str(round(test_info["queries per millisec"]*1000, 2))
    output+= " latency[us]: mean " +  str(test_info["latency mean"])
    output+= " max " + str(test_info["latency max"])
    output+= " min " +  str(test_info["latency min"])
    output+= " client exe  " + test_info["clientName"]
    output+= " server exe " + test_info["serverName"]
    return output

def get_csv_header():
    #return "client tech, server tech, requests number, total time[ms], queries per millisec, latency mean[us], latency max[us], latency min[us]"
    return "client tech, server tech, requests number, total time, unit, latency mean[us], latency max[us], latency min[us]"

def format_to_csv(test_info):
    #return test_info["client"] + "," + test_info["server"] + "," + str(test_info["requests"]) + "," + str(test_info["total time"]) + "," + str(test_info["queries per millisec"]) + "," + str(test_info["latency mean"]) + "," + str(test_info["latency max"]) + "," + str(test_info["latency min"])
    return test_info["client"] + "," + test_info["server"] + "," + str(test_info["requests"]) + "," + str(test_info["total time"]) + "," + test_info["total time unit"] + ","  + str(test_info["latency mean"]) + "," + str(test_info["latency max"]) + "," + str(test_info["latency min"])

def prepareTestInfo(outcome_lines, server, client, tech_mapping):

    serverTechnology, serverName = getTechnologyAndName(server, tech_mapping)
    clientTechnology, clientName = getTechnologyAndName(client, tech_mapping)

    testDurationUnit, testDuration = getInfoFromOutputTimeDuration(outcome_lines, TEST_TIME_SEARCH_TEXT)
    mesagesNo = int(getInfoFromOutput(outcome_lines, EXECUTION_NUMBER_SEARCH_TEXT).strip())
    clientsNo = int(getInfoFromOutput(outcome_lines, CLIENT_NUMBER_SEARCH_TEXT).strip())
    isLatencyPresent, latency_mean, latency_max, latency_min = getLatencies(outcome_lines)
    #qpms = 0
    #testDuration
    #if testDuration != 0 :
    #    qpms = ((mesagesNo*clientsNo)/testDuration)

    testInfo = {
      "requests": mesagesNo,
      "total time unit": testDurationUnit,
      "total time": testDuration, #[ms]
      "client": clientTechnology,
      "server": serverTechnology,
      #"queries per millisec": qpms,
      "clientName" : clientName,
      "serverName" : serverName,
      "isLatencyPresent" : isLatencyPresent,
      "latency mean" : latency_mean, #[us]
      "latency min" : latency_min, #[us]
      "latency max" : latency_max, #[us]
    }

    return testInfo


def getTechnologyAndName(executablePath, mapping):
    for technology, path in mapping.items():
        tech_index = executablePath.find(path)
        if tech_index != -1:
            end_index = executablePath.find(" ", tech_index+ len(path))
            if end_index == -1:
                return technology, executablePath[tech_index+ len(path) +1 : len(executablePath)]
            return technology, executablePath[tech_index+ len(path)+1: end_index]
    return "not identified", executablePath

if __name__ == "__main__":
    main()