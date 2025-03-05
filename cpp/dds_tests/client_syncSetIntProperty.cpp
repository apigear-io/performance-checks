#include <memory>
#include <chrono>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include "dds_client.h"
#include <vector>
#include "HelloWorldSubscriber.h"

int main(int argc, char* argv[])
{
    std::vector<uint16_t> timePerMessage;
    auto sendThreadNumber = 1u;
    auto messages_number = 10u;
    if (argc > 1)
    {
        char* p;
        messages_number = strtol(argv[1], &p, 10);
    }
    if (argc > 2)
    {
        char* p;
        sendThreadNumber = strtol(argv[2], &p, 10);
    }

    Cpp::Api::TestApiClient client("client" + std::to_string(messages_number));
    client.init();

    bool keepRunning = true;
    int p = 6;
    std::string cmd;
    do {
        std::cout << "Enter command:" << std::endl;
        getline(std::cin, cmd);
 
        if (cmd == "quit") {
            keepRunning = false;
        }
        if (cmd == "prop")
        {
            client.requestPropertyChange(p++);
        }
        if (cmd == "m")
        {
            client.remoteMethodCall(p);
        }
    } while (keepRunning);

    return 0;
}