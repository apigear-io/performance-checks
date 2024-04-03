
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
    def __init__(self, relative_file_path, cpp_build_path, qt_build_path, unreal_test_dir):

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
                element = setPathsAndFormat(line, cpp_build_path, qt_build_path, unreal_test_dir)
                self.servers.append(element)
            elif  readingClients:
                element = setPathsAndFormat(line, cpp_build_path, qt_build_path, unreal_test_dir)
                self.clients.append(element)

def setPathsAndFormat(line, cpp_build_path, qt_build_path, unreal_test_dir):
    element = line.rstrip('\n');
    element = element.replace("CPP_BUILD", cpp_build_path);
    element = element.replace("QT_BUILD", qt_build_path);
    element = element.replace("UNREAL_DIR", unreal_test_dir);
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
    cpp_build_path = ""
    qt_build_path = ""
    unreal_test_dir = ""
    args = sys.argv[1:]
    if len(args) > 0:
        scenarioPath = args[0]
    if len(args) > 1:
        cpp_build_path = args[1]
    if len(args) > 2:
        qt_build_path = args[2]
    if len(args) > 3:
        unreal_test_dir = args[3]
    
    bin_paths = [cpp_build_path, qt_build_path, unreal_test_dir]
    tech_mapping = {"cpp": cpp_build_path, "qt":qt_build_path, "unreal":unreal_test_dir}
    current_scenario = scenario(scenarioPath, cpp_build_path, qt_build_path, unreal_test_dir);

    print(current_scenario.servers)
    print(current_scenario.clients)
    firstLine = "scenario: " + scenarioPath
    linesToWriteResult = [  firstLine ]
    linesToWriteCsv = [  firstLine ]
    linesToWriteCsv.append(get_csv_header())
    for client in current_scenario.clients:
        client_args = prepareClientProcess(client, bin_paths);
        if len(client_args) == 0:
            return 1
        for server in current_scenario.servers:
            server = removePostfixIfNoOriginalFile(server)
            if not os.path.isfile(server):
                print("File doesn't exist: " + server)
                return 1
            try:
                server_proces = None
                client_proces = None
                server_proces = subprocess.Popen(server, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
                sleep(1)
                if len(client_args) == 0:
                    if server_proces != None:
                        server_proces.kill()
                    print("client not found in line")
                    print(client)
                    return 1
                if client_args[0].startswith(SHELL):
                    client_proces = subprocess.Popen(client_args[1], shell=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
                else:
                    client_proces = subprocess.Popen(client_args, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
                try:
                    server_proces.wait(150)
                    client_proces.wait(150)
                except subprocess.TimeoutExpired:
                    server_proces.kill()
                    client_proces.kill()
                    print("Timeout for pair: ")
                    print(client)
                    print(client_proces.communicate()[0].decode)
                    print(server)
                    print(server_proces.communicate()[0].decode)
                    return 1
            except Exception as e:
                if server_proces != None:
                    server_proces.kill()
                if client_proces != None:
                    client_proces.kill()
                raise
            server_outcome_lines = unify_delimeters_and_split(server_proces.communicate()[0].decode())
            client_outcome_lines = unify_delimeters_and_split(client_proces.communicate()[0].decode())
            if (len(server_outcome_lines[0]) == 0):
                if server_proces != None:
                    server_proces.kill()
                print("someting went wrong when running " + server + " check if your exe can be run")
                continue
            if (len(client_outcome_lines[0]) == 0):
                print("someting went wrong when running " + client + ", check if your exe can be run")
                if client_proces != None:
                    client_proces.kill()
                continue
            test_info = prepareTestInfo(client_outcome_lines, server, client, tech_mapping)
            formated_line = format_for_output(test_info)
            print(formated_line)
            linesToWriteResult.append(formated_line)
            linesToWriteCsv.append(format_to_csv(test_info))
            sleep(2)
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

# On Linux delimeter is only \n, replacing \r\n with \n makes split work on Linux and Windows platform
def unify_delimeters_and_split(lines):
    return lines.replace('\r\n', '\n').split('\n')

def getInfoFromOutput(lines, search_text):
    for line in lines:
        if (line.find(search_text) != -1):
            outcome = line.split(':')
            return outcome[1]
    return "0"

def getLatencies(lines):
    for line in lines:
        if line.startswith("Latency"):
            outcome = line.split(' ')
            if len(outcome) > 6:
                return True, outcome[2], outcome[4], outcome[6],
    return False, -1, -1, -1 

def format_for_output(test_info):
    output =   "client " + test_info["client"] 
    output+= " server " + test_info["server"]
    output+= " requests number " + str(test_info["requests"])
    output+= " total time[ms] " +  str(test_info["total time"])
    output+= " queries per ms " + str(round(test_info["queries per millisec"]*1000, 2))
    output+= " latency[us]: mean " +  str(test_info["latency mean"])
    output+= " max " + str(test_info["latency max"])
    output+= " min " +  str(test_info["latency min"])
    output+= " client exe  " + test_info["clientName"]
    output+= " server exe " + test_info["serverName"]
    return output

def get_csv_header():
    return "client tech, server tech, requests number, total time[ms], queries per millisec, latency mean[us], latency max[us], latency min[us]"

def format_to_csv(test_info):
    return test_info["client"] + "," + test_info["server"] + "," + str(test_info["requests"]) + "," + str(test_info["total time"]) + "," + str(test_info["queries per millisec"]) + "," + str(test_info["latency mean"]) + "," + str(test_info["latency max"]) + "," + str(test_info["latency min"])

def prepareTestInfo(outcome_lines, server, client, tech_mapping):

    serverTechnology, serverName = getTechnologyAndName(server, tech_mapping)
    clientTechnology, clientName = getTechnologyAndName(client, tech_mapping)

    testDuration = int(getInfoFromOutput(outcome_lines, TEST_TIME_SEARCH_TEXT).strip())
    mesagesNo = int(getInfoFromOutput(outcome_lines, EXECUTION_NUMBER_SEARCH_TEXT).strip())
    clientsNo = int(getInfoFromOutput(outcome_lines, CLIENT_NUMBER_SEARCH_TEXT).strip())
    isLatencyPresent, latency_mean, latency_max, latency_min = getLatencies(outcome_lines)
    qpms = 0
    if testDuration != 0 :
        qpms = ((mesagesNo*clientsNo)/testDuration)

    testInfo = {
      "requests": mesagesNo,
      "total time": testDuration, #[ms]
      "client": clientTechnology,
      "server": serverTechnology,
      "queries per millisec": qpms,
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