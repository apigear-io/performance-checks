#include <memory>
#include <chrono>
#include <iostream>
#include <algorithm>
#include <future>
#include <QCoreApplication>
#include <thread>

/**
Template for simple scenario. This is successful case scenario.
@param TestData a test object with testFunction(uint32_t) method, where an uint32_t parameter is current function execution number .
@param networkProtocolHandler An object which is able to prepare/tear down a connection and use it with testData (plug in/out if necessary).
@param execute_times number of times the function should be executed on a single testData object.

The scenario:
The connection is set up, and all the testData objects are connected
Then simultaneously for each object we start executing a testFunction in a loop. The function is called execute_times number for each object.
You can use waitForReturnMessages function (in networkProtocolHandler) for controlling test end if you expect server to send back any messages.
It is executed after all testFunctions are fired up.
Use disconnectObjects function (networkProtocolHandler) to properly close connection for each object.

WARNING after test ends it quits application.
*/
template <class TestData, class NetworkProtocolHandler>
std::future<void> executeTestFunction(std::vector<TestData>& testData, NetworkProtocolHandler& networkProtocolHandler, uint32_t execute_times)
{
    networkProtocolHandler.prepareConnection();


    auto clientThread = std::async(std::launch::async,
        [execute_times, &testData, &networkProtocolHandler]() {

        std::vector<std::shared_future<void>> tasks;
            networkProtocolHandler.connectObjects(testData);

            auto begin = std::chrono::high_resolution_clock::now();
            for (auto& element : testData)
            {
                auto sendMessagesTask = std::async(std::launch::async,
                    [&element, execute_times, &networkProtocolHandler]() {
                        networkProtocolHandler.waitUntilObjectConnected(element);
                        for (auto i = 0; i < execute_times; i++)
                        {
                            element.testFunction(i + 1);
                        }
                    });
                // Extend scope of task, not to wait here in a function for it to be over.
                tasks.push_back(sendMessagesTask.share());
            }

            networkProtocolHandler.waitForReturnMessages(testData, execute_times);
            networkProtocolHandler.disconnectObjects(testData);

            auto end = std::chrono::high_resolution_clock::now();
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
            std::cout << "Time measured: " << time.count() << std::endl;
            std::cout << "Objects number: " << testData.size() << std::endl;
            std::cout << "Function execution number for each object: " << execute_times << std::endl;
            QCoreApplication::quit();
        });

    return clientThread;
}
