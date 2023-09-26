
import os.path
import sys
from subprocess import Popen, TimeoutExpired
import subprocess
from time import sleep

TEST_TIME_SEARCH_TEXT = "Time measured:" 
CLIENT_NUMBER_SEARCH_TEXT = "Objects number:"
EXECUTION_NUMBER_SEARCH_TEXT = "Function execution number for each object:"


#requires CPP_BUILD and QT_BUILD to point to output
class scenario:
    def __init__(self, relative_file_path, cpp_build_path, qt_build_path):

        self.servers = []
        self.clients = []
        self.client_execution_parameters = []
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
            elif line.lstrip().startswith('['):
                self.client_execution_parameters = line.strip('[').rstrip('\n').rstrip(']').split()
            elif  readingServers:
                element = line.rstrip('\n');
                if element.lstrip().startswith("CPP_BUILD"):
                    element = element.strip("CPP_BUILD")
                    element = cpp_build_path + element
                if element.lstrip().startswith("QT_BUILD"):
                    element = element.strip("QT_BUILD")
                    element = qt_build_path + element
                self.servers.append(element)
            elif  readingClients:
                element = line.rstrip('\n');
                if element.lstrip().startswith("CPP_BUILD"):
                    element = element.strip("CPP_BUILD")
                    element = cpp_build_path + element
                if element.lstrip().startswith("QT_BUILD"):
                    element = element.strip("QT_BUILD")
                    element = qt_build_path + element
                self.clients.append(element)


def main():
    scenarioPath =""
    cpp_build_path = ""
    qt_build_path = ""
    args = sys.argv[1:]
    if len(args) > 0:
        scenarioPath = args[0]
    if len(args) > 1:
        cpp_build_path = args[1]
    if len(args) > 2:
        qt_build_path = args[2]

    current_scenario = scenario(scenarioPath, cpp_build_path, qt_build_path);

    print(current_scenario.servers)
    print(current_scenario.clients)
    firstLine = "scenario: " + scenarioPath
    linesToWrite = [  firstLine ]
    for parameter in current_scenario.client_execution_parameters:
        linesToWrite.append("client parameter: "+ str(parameter))
        for client in current_scenario.clients:
            if not os.path.isfile(client):
                print("Client file doesn't exist")
                return -1
            for server in current_scenario.servers:
                if not os.path.isfile(server):
                    print("Server file doesn't exist")
                    return -1
                p1 = subprocess.Popen(server, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
                sleep(0.4)
                p2 = subprocess.Popen(client + " " + parameter, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
                try:
                    p1.wait(60)
                    p2.wait(60)
                except subprocess.TimeoutExpired:
                    p1.kill()
                    p2.kill()
                    print("Timeout for pair")
                    print(client)
                    print(server)
                    return -1
                server_outcome_lines = p1.communicate()[0].decode().split('\r\n')
                client_outcome_lines = p2.communicate()[0].decode().split('\r\n')
                if (len(server_outcome_lines[0]) == 0):
                    print("someting went wrong when running test, check if your exe can be run")
                    print("running " + server)
                    continue
                if (len(client_outcome_lines[0]) == 0):
                    print("someting went wrong when running test, check if your exe can be run")
                    print("running " + client)
                    continue
                test_info = prepareTestInfo(client_outcome_lines, server, client, scenarioPath)
                print(test_info)
                linesToWrite.append(test_info)
                sleep(0.4)
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


def prepareTestInfo(outcome_lines, server, client, scenarioPath):

    serverTechnology, serverName = getTechnologyAndName(server)
    clientTechnology, clientName = getTechnologyAndName(client)

    testDuration = int(getInfoFromOutput(outcome_lines, TEST_TIME_SEARCH_TEXT).strip())
    mesagesNo = int(getInfoFromOutput(outcome_lines, EXECUTION_NUMBER_SEARCH_TEXT).strip())
    clientsNo = int(getInfoFromOutput(outcome_lines, CLIENT_NUMBER_SEARCH_TEXT).strip())
    
    #no msg size info from test!
    #Time measured: 1025', 'Objects number: 1', 'Function execution number for each object: 10000'
    #test_info += " | msg format: " + "JSON"
    #test_info += " | msg size: NO INFO"
    test_info = "Clients number: " + str(clientsNo)
    test_info += " | msgs per client: " + str(mesagesNo)
    test_info += " | Tech: client " + clientTechnology
    test_info += "; server " + serverTechnology
    test_info += " | test time [ms]: " + str(testDuration)
    #test_info += " | max time: NO INFO"
    #test_info += " | min time: NO INFO"
    #test_info += " | number of runs: NO INFO"
    throughput = format(((mesagesNo*2*clientsNo)/testDuration), ".2f")
    test_info += " | avg. throughput [msgs/ms]: " + throughput
    test_info += " | client: " + clientName
    test_info += " | server: " + serverName
    return test_info


def getTechnologyAndName(executablePath):
    exeInfo = executablePath.split("/");
    exeInfo = list(filter(("..").__ne__, exeInfo))
    exeInfo = list(filter((".").__ne__, exeInfo))
    exeTechnology = exeInfo[0];
    if exeTechnology.find("build-qt") != -1:
        exeTechnology = "qt"
    exeName = exeInfo[len(exeInfo) - 1 ]
    return exeTechnology, exeName

if __name__ == "__main__":
    main()