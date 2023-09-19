
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
                if element.lstrip().startswith("CPP_BUILD")
                    element = element.strip("CPP_BUILD")
                    element = cpp_build_path + element
                if element.lstrip().startswith("QT_BUILD")
                    element = element.strip("QT_BUILD")
                    element = qt_build_path + element
                self.servers.append(element)
            elif  readingClients:
                element = line.rstrip('\n');
                if element.lstrip().startswith("CPP_BUILD")
                    element = element.strip("CPP_BUILD")
                    element = cpp_build_path + element
                if element.lstrip().startswith("QT_BUILD")
                    element = element.strip("QT_BUILD")
                    element = qt_build_path + element
                self.clients.append(line.rstrip('\n'))


def main():
    scenarioPath =""
    args = sys.argv[1:]
    if len(args) == 1:
        scenarioPath = args[0]
        
    current_scenario = scenario(scenarioPath);

    print(current_scenario.servers)
    print(current_scenario.clients)
    for parameter in current_scenario.client_execution_parameters:
        for server in current_scenario.servers:
            if not os.path.isfile(server):
                print("Server file doesn't exist")
                return
            for client in current_scenario.clients:
                if not os.path.isfile(client):
                    print("Client file doesn't exist")
                    return
                p1 = subprocess.Popen(server, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
                sleep(0.4)
                p2 = subprocess.Popen(client + " " + parameter, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
                try:
                    p1.wait(120)
                    p2.wait(120)
                except subprocess.TimeoutExpired:
                    p1.kill()
                    p2.kill()
                    print("Timeout for pair")
                    print(client)
                    print(server)
                    return
                server_outcome_lines = p1.communicate()[0].decode().split('\r\n')
                client_outcome_lines = p2.communicate()[0].decode().split('\r\n')
                test_info = prepareTestInfo(client_outcome_lines, server, client, scenarioPath)
                print(test_info)
                sleep(0.4)


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
    test_info = "scenario: " + scenarioPath
    #test_info += "| msg format: " + "JSON"
    #test_info += "| msg size: NO INFO"
    test_info += "| number of clients: " + str(clientsNo)
    test_info += "| client technology: " + clientTechnology
    test_info += "| client name: " + clientName
    test_info += "| server technology: " + serverTechnology
    test_info += "| server name: " + serverName
    test_info += "| average time: [ms] " + str(testDuration)
    #test_info += "| max time: NO INFO"
    #test_info += "| min time: NO INFO"
    #test_info += "| number of runs: NO INFO"
    test_info += "| messages number per client: " + str(mesagesNo)
    test_info += "| average throughput:" + str(((mesagesNo*clientsNo)/testDuration)/2) + " [messages/ms]"
    return test_info


def getTechnologyAndName(executablePath):
    exeInfo = executablePath.split("/");
    exeInfo = list(filter(("..").__ne__, exeInfo))
    exeTechnology = exeInfo[0];
    if exeTechnology.find("build-qt") != -1:
        exeTechnology = "qt"
    exeName = exeInfo[len(exeInfo) - 1 ]
    return exeTechnology, exeName

if __name__ == "__main__":
    main()