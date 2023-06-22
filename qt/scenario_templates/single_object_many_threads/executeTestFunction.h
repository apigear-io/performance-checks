#include <memory>
#include <chrono>
#include <iostream>
#include <algorithm>
#include <future>
#include <QCoreApplication>

/**
Template for simple scenario. This is successful case scenario.
@param TestData a test object with testFunction(uint32_t) method, where an uint32_t parameter is current function execution number .
@param networkProtocolHandler An object which is able to prepare/tear down a connection and use it with testData (plug in/out if necessary).
@param execute_times number of times the function should be executed on a testData object in one of threads.
@param threadNo number of threads in which simultaneously the function should be executed on a testData object.

The scenario:
The connection is set up, and the testData object is connected
Then simultaneously for each thread we start executing a testFunction in a loop. The function is called execute_times number for each thread.
You can use waitForReturnMessages function (in networkProtocolHandler) for controlling test end if you expect server to send back any messages.
It is executed after all testFunctions are fired up.
Use disconnectObjects function (networkProtocolHandler) to properly close connection for each object.

WARNING after test ends it quits application.
*/
template <class TestData, class NetworkProtocolHandler>
std::future<void> executeTestFunction(TestData& testObject, NetworkProtocolHandler& networkProtocolHandler, uint32_t execute_times, uint32_t threadCount)
{
    auto portNumber = 8000;
    auto hostAddress = "127.0.0.1";
    networkProtocolHandler.prepareConnection(hostAddress, portNumber);

    auto clientThread = std::async(std::launch::async,
        [threadCount, execute_times, &testObject, &networkProtocolHandler](){


        std::vector<std::shared_future<void>> tasks;
        auto begin = std::chrono::high_resolution_clock::now();

        std::vector<TestData> testData = { testObject };
        networkProtocolHandler.connectObjects(testData);
        networkProtocolHandler.waitUntilObjectConnected(testObject);

        for (int threadNo = 0u; threadNo < threadCount; threadNo++)
        {
            auto sendMessagesTask = std::async(std::launch::async,
                [&testObject, execute_times, &tasks, threadNo]() {
                for (auto i = 0u; i < execute_times; i++)
                {
                    testObject.testFunction(threadNo * execute_times + i);
                }
                });
            tasks.push_back(sendMessagesTask.share());
        }

        for (auto task : tasks)
        {
            task.wait();
        }
        networkProtocolHandler.waitForReturnMessages(testData, threadCount * execute_times );
        networkProtocolHandler.disconnectObjects(testData);

        auto end = std::chrono::high_resolution_clock::now();

        auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        std::cout << "Time measured: " << time.count() << std::endl;
        std::cout << "Objects number: 1" << std::endl;
        std::cout << "Function execution number for each object: " << threadCount * execute_times << std::endl;
        QCoreApplication::quit();
    });
    return clientThread;
}
