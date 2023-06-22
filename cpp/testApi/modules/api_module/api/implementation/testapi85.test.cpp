#include <memory>
#include "catch2/catch.hpp"
#include "api/implementation/testapi85.h"

using namespace Cpp::Api;
TEST_CASE("Testing TestApi85", "[TestApi85]"){
    std::unique_ptr<ITestApi85> testTestApi85 = std::make_unique<TestApi85>();
    // setup your test
    SECTION("Test operation funcInt") {
        // Do implement test here
        testTestApi85->funcInt(0);
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testTestApi85->funcFloat(0.0f);
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testTestApi85->funcString(std::string());
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testTestApi85->setPropInt(0);
        REQUIRE( testTestApi85->getPropInt() == 0 );
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testTestApi85->setPropFloat(0.0f);
        REQUIRE( testTestApi85->getPropFloat() == Approx( 0.0f ) );
    }
    SECTION("Test property propString") {
        // Do implement test here
        testTestApi85->setPropString(std::string());
        REQUIRE( testTestApi85->getPropString() == std::string() );
    }
}
