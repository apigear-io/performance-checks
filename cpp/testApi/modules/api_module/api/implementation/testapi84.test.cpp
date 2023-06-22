#include <memory>
#include "catch2/catch.hpp"
#include "api/implementation/testapi84.h"

using namespace Cpp::Api;
TEST_CASE("Testing TestApi84", "[TestApi84]"){
    std::unique_ptr<ITestApi84> testTestApi84 = std::make_unique<TestApi84>();
    // setup your test
    SECTION("Test operation funcInt") {
        // Do implement test here
        testTestApi84->funcInt(0);
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testTestApi84->funcFloat(0.0f);
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testTestApi84->funcString(std::string());
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testTestApi84->setPropInt(0);
        REQUIRE( testTestApi84->getPropInt() == 0 );
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testTestApi84->setPropFloat(0.0f);
        REQUIRE( testTestApi84->getPropFloat() == Approx( 0.0f ) );
    }
    SECTION("Test property propString") {
        // Do implement test here
        testTestApi84->setPropString(std::string());
        REQUIRE( testTestApi84->getPropString() == std::string() );
    }
}
