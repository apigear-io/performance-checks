#project purpose:
Tests were created to find bottle necks in templates to run under performance profiler tool(e.g. Visual Studio Performance Profiler)
They also provide some time measurements which may be used to compare different technologies and protocols, or just give more-less information about possible efficiency.
Also they check multithread using many or single objects.

Tests do not use any test framework - to exclude 3rd party calls
Tests use generated implementation of apigear/performance_interface.module for test sinks and source - this contains basic API which is then replicated 100 with apigear/GenerateIdl.py script stored in apigear\performance_interface100.module.yaml. This file is then used for performance.solution.yaml
Performance.solution.yaml contains all technologies for which API is generated and used for tests.

TEST RESULTS ARE AVAILABLE IN JOBS

#project content

Repository contains tests for different technologies - goal would be that server and client have same scenarios so the execution time can be compared cross -technology.
Ideally you could not only server and client in same tchnology but also  run client scenario in technology A and a server in technology B.

Repository content:
apigear - interface used for tests and solution file to generate a code for desired technologies (if you add a technology, extend this file)
technology folders e.g. qt - contains: generated code, tests.

The test scenario is determined with client part. Each test_client_... is a separate scenario.
The server part only responds to client requests with default implementation (so only changing propetis works out of the box, for other tests the implementation more logic must be provided)
- it registers one or all objects (depending if version for single or many objects was run)
- on receive (first) link message it starts time measurement
- it responses any message it receives - using logic implemented in the testApi/modules/api_module/api/implementation
- time measurement ends when last unlink message is received, server starts closing procedure and the program ends.

To run test:
1. Start server side - either from console or using performance profiler
2. Start one of client side tests - either from console or using performance profiler 
OR use test runner with test scenarios it runs all listed servers with all listed clients
the parameter list [] next to client contains a message number to be send from single thread.
Have in mind that you need to make sure that executables find all the neceassry dlls (either set paths for them or just copy the dlls into the folders).


Real object with network layer are used for tests.
In case the sinks and sources need to be regenerated please do following:
1. Make sure the API file is in shape you want `performance\apigear\performance_interface.module.yaml`
2. Use The `performance\apigear\GenerateIdl.py' to generate `performance\apigear\performance_interface100.module.yaml` which contains this api generated 100 times with a number added to the name.
3. Make sure the solution file `performance\apigear\performance.solution.yaml` generates the olink and stubs feature and it uses template-cpp14 and regenerate the api

