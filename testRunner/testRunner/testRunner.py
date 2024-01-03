
import os.path
import sys
from subprocess import Popen, TimeoutExpired
import subprocess
from time import sleep

TEST_TIME_SEARCH_TEXT = "Time measured:" 
CLIENT_NUMBER_SEARCH_TEXT = "Objects number:"
EXECUTION_NUMBER_SEARCH_TEXT = "Function execution number for each object:"


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
            if line.lstrip().startswith('servers:'):
                readingServers = True
                readingClients = False
            elif line.lstrip().startswith('clients:'):
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
    element.lstrip()
    element = element.replace("CPP_BUILD", cpp_build_path);
    element = element.replace("QT_BUILD", qt_build_path);
    element = element.replace("UNREAL_DIR", unreal_test_dir);
    return element;
    
def checkFileExists(file_path):
    if not os.path.isfile(file_path):
        file_path = file_path.rstrip('.exe')
        if not os.path.isfile(file_path):
            print("File doesn't exist: " + file_path)
            return 1
    return 0
            
def getFileFromClientLine(client_line, paths):
    for path in paths:
        start_index = client_line.find(path)
        if start_index != -1:
            end_index = client_line.find(" ", start_index+ len(path))
            if end_index == -1:
                return client_line[start_index:len(client_line)-1]
            client_name = client_line[start_index: end_index]
            client_name = client_name.rstrip("\"")
            return client_name
    return client_line

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
    
    paths = [cpp_build_path, qt_build_path, unreal_test_dir]
    tech_mapping = {"cpp": cpp_build_path, "qt":qt_build_path, "unreal":unreal_test_dir}
    current_scenario = scenario(scenarioPath, cpp_build_path, qt_build_path, unreal_test_dir);

    print(current_scenario.servers)
    print(current_scenario.clients)
    firstLine = "scenario: " + scenarioPath
    linesToWrite = [  firstLine ]
    for client in current_scenario.clients:
        clientFile = getFileFromClientLine(client, paths)
        if checkFileExists(clientFile) != 0:
           return 1
        for server in current_scenario.servers:
            if checkFileExists(server) != 0:
                return 1
            server_proces = subprocess.Popen(server, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
            sleep(1)
            client_proces = subprocess.Popen(client, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
            try:
                server_proces.wait(300)
                client_proces.wait(300)
            except subprocess.TimeoutExpired:
                server_proces.kill()
                client_proces.kill()
                print("Timeout for pair")
                print(client)
                print(client_proces.communicate()[0].decode())
                print(server)
                print(server_proces.communicate()[0].decode())
                return 1
            # On Linux delimeter is only \n, replacing \r\n with \n makes split work on Linux and Windows platform
            server_outcome_lines = server_proces.communicate()[0].decode().replace('\r\n', '\n').split('\n')
            client_outcome_lines = client_proces.communicate()[0].decode().replace('\r\n', '\n').split('\n')
            if (len(server_outcome_lines[0]) == 0):
                print("someting went wrong when running test, check if your exe can be run")
                print("running " + server)
                continue
            print("server info")
            print(server_outcome_lines)
            if (len(client_outcome_lines[0]) == 0):
                print("someting went wrong when running test, check if your exe can be run")
                print("running " + client)
                continue
            test_info = prepareTestInfo(client_outcome_lines, server, client, scenarioPath, tech_mapping)
            print(test_info)
            linesToWrite.append(test_info)
            sleep(1)
    scenarioPath = scenarioPath.split("/")
    resultFileName = "report_" +  scenarioPath[len(scenarioPath) -1]
    output_file = open(resultFileName,'w')
    output_file.writelines(line + '\n' for line in linesToWrite)
    return 0


def getInfoFromOutput(lines, search_text):
    for line in lines:
        if (line.find(search_text) != -1):
            outcome = line.split(':')
            return outcome[1]
    return "0"


def prepareTestInfo(outcome_lines, server, client, scenarioPath, tech_mapping):

    serverTechnology, serverName = getTechnologyAndName(server, tech_mapping)
    clientTechnology, clientName = getTechnologyAndName(client, tech_mapping)

    testDuration = int(getInfoFromOutput(outcome_lines, TEST_TIME_SEARCH_TEXT).strip())
    mesagesNo = int(getInfoFromOutput(outcome_lines, EXECUTION_NUMBER_SEARCH_TEXT).strip())
    clientsNo = int(getInfoFromOutput(outcome_lines, CLIENT_NUMBER_SEARCH_TEXT).strip())
    
    #no msg size info from test!
    #Time measured: 1025', 'Objects number: 1', 'Function execution number for each object: 10000'
    #test_info += " | msg format: " + "JSON"
    #test_info += " | msg size: NO INFO"
    test_info = "Clients number: " + str(clientsNo)
    test_info += " | msgs per client: " + str(mesagesNo)
    test_info += " | test time [ms]: " + str(testDuration)
    test_info += " | Tech: client " + clientTechnology
    test_info += "; server " + serverTechnology
    #test_info += " | max time: NO INFO"
    #test_info += " | min time: NO INFO"
    #test_info += " | number of runs: NO INFO"
    throughput = format(((mesagesNo*2*clientsNo)/testDuration), ".2f")
    test_info += " | avg. throughput [msgs/ms]: " + throughput
    test_info += " | client: " + clientName
    test_info += " | server: " + serverName
    return test_info


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