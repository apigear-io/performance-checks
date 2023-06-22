#include <memory>
#include "catch2/catch.hpp"
#include "api/implementation/testapi35.h"

using namespace Cpp::Api;
TEST_CASE("Testing TestApi35", "[TestApi35]"){
    std::unique_ptr<ITestApi35> testTestApi35 = std::make_unique<TestApi35>();
    // setup your test
    SECTION("Test operation funcInt") {
        // Do implement test here
        testTestApi35->funcInt(0);
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testTestApi35->funcFloat(0.0f);
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testTestApi35->funcString(std::string());
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testTestApi35->setPropInt(0);
        REQUIRE( testTestApi35->getPropInt() == 0 );
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testTestApi35->setPropFloat(0.0f);
        REQUIRE( testTestApi35->getPropFloat() == Approx( 0.0f ) );
    }
    SECTION("Test property propString") {
        // Do implement test here
        testTestApi35->setPropString(std::string());
        REQUIRE( testTestApi35->getPropString() == std::string() );
    }
}
