# Project purpose:
Tests were created to find bottle necks in templates to run under performance profiler tool(e.g. Visual Studio Performance Profiler)
They also provide some time measurements which may be used to compare different technologies and protocols, or just give more-less information about possible efficiency.
Also they check multithread using many or single objects.

Tests do not use any test framework - to exclude 3rd party calls
Tests use generated implementation of apigear/performance_interface0.module for test sinks and source, which is used to prepare version for one object only. The apigear/performance_interface100.module contains the basic API which is then replicated 100 with "apigear/GenerateIdl.py" script. The "performance.solution.yaml" uses apigear/performance_interface0.module. To use many objects use "performance100.solution.yaml"
Solution files contain all technologies for which API is generated and used for tests.

TEST RESULTS ARE AVAILABLE IN JOBS
For latest results go to actions tab of https://github.com/apigear-io/performance-checks
choose latest, find "Technology Template Build Test" action. Choose a job for Windos, Ubuntu or MacOs.
For now you can find results when unfold the "RUN scenario" step.

# Project content

Repository contains tests for different technologies - goal is that server and client have same scenarios so the execution time can be compared across technologies.

Repository content:
- apigear - interface used for tests and solution file to generate a code for desired technologies (if you add a technology, extend this file)
- technology folders e.g. qt - with:
    -  generated code - "testApi" folder
    -  test scenarios - should contain general, protocol independent scenario
    -  specific technology infrastructure required to run scenario i.e  network protocol handler adapter for technology - this is used by scenarios, and the actual tests that just execute the scenarios with specific data types.

The test scenario is determined with client part. Each test client is a separate scenario.
Example scenario sets up test object and requests a property change specified number of times in a loop from few threads (all at once in this case), then waits for the property to be set exactly that number of times. Then it finises test. 
The server part only responds to client requests with default implementation (so only changing properties works out of the box, for testing signals and methods some logic needs to implemented).
The client and server part need to have agree on start and stop conditions. 
For OLink start and stop is determined with OLink link and unlink messages (so the server stops on receiving last unlink message, the client stops after sending last unlink message - but having all the required property changes from server side first).
The Mqtt tests are using extra message send by client.

## Running tests locally
1. Download this repository
2. Use APIGEAR to generate the code (for now it generates cpp and qt test objects), see the solution file apigear\performance.solution.yaml
3. Build projects cpp/CMakeLists.txt and qt/CMakeLists.txt

Now you can either run manually pair server and client (you can mix cpp and qt, but you cannot mix features mqtt and olink).
You can use your profiling tool for that.
In case of OLink remember to start server first.
In case of Mqtt remember to start broker of your choice.

OR

Use test runner with test scenarios.
The test runner is located in "testRunner/testRunner", scenarios are under "testRunner/testRunner/scenarios".
The test runner executes all listed executables with their arguments in a scenario: servers and clients. At one time only one server with and client is run - the runner waits till each pair finishes the work and then runs next one - all servers are run with all the clients.

Running a test runner from a root of this repository:
on windows:
py testRunner/testRunner/testRunner.py "testRunner/testRunner/scenarios/olink_single_object_setProperty.txt" "relative-path-to-cpp-executables-used-by-scenario" "relative-path-to-qt-executables-used-by-scenario"
unix:
python testRunner/testRunner/testRunner.py "testRunner/testRunner/scenarios/olink_single_object_setProperty.txt" "relative-path-to-cpp-executables-used-by-scenario" "relative-path-to-qt-executables-used-by-scenario"

Have in mind that you need to make sure that executables find all the necessary dlls (either set paths for them or just copy the dlls into the folders). Test runner produces reports in main directory.


### Changing an API
Real object with network layer are used for tests.
In case the sinks and sources need to be regenerated please do following:
1. Make sure the API file is in shape you want `performance\apigear\performance_interface.module.yaml`
2. Use The `performance\apigear\GenerateIdl.py' to generate `performance\apigear\performance_interface100.module.yaml` which contains this api generated 100 times with a number added to the name.
3. Make sure the solution file `performance\apigear\performance.solution.yaml` generates the olink and stubs feature and it uses template-cpp14 and regenerate the api

OBJECT LINK CORE ONLY TESTS

Tests created without the network layer. They connect client's write function with server's handle message, and server's write function with client's handle message.
The are added for cpp template for now.
They can be run just by starting a test target. It contains both server and client side in one app, as no network is required.
