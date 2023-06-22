#include <memory>
#include "catch2/catch.hpp"
#include "api/implementation/testapi3.h"

using namespace Cpp::Api;
TEST_CASE("Testing TestApi3", "[TestApi3]"){
    std::unique_ptr<ITestApi3> testTestApi3 = std::make_unique<TestApi3>();
    // setup your test
    SECTION("Test operation funcInt") {
        // Do implement test here
        testTestApi3->funcInt(0);
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testTestApi3->funcFloat(0.0f);
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testTestApi3->funcString(std::string());
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testTestApi3->setPropInt(0);
        REQUIRE( testTestApi3->getPropInt() == 0 );
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testTestApi3->setPropFloat(0.0f);
        REQUIRE( testTestApi3->getPropFloat() == Approx( 0.0f ) );
    }
    SECTION("Test property propString") {
        // Do implement test here
        testTestApi3->setPropString(std::string());
        REQUIRE( testTestApi3->getPropString() == std::string() );
    }
}
