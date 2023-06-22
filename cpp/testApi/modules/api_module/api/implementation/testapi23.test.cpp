#include <memory>
#include "catch2/catch.hpp"
#include "api/implementation/testapi23.h"

using namespace Cpp::Api;
TEST_CASE("Testing TestApi23", "[TestApi23]"){
    std::unique_ptr<ITestApi23> testTestApi23 = std::make_unique<TestApi23>();
    // setup your test
    SECTION("Test operation funcInt") {
        // Do implement test here
        testTestApi23->funcInt(0);
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testTestApi23->funcFloat(0.0f);
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testTestApi23->funcString(std::string());
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testTestApi23->setPropInt(0);
        REQUIRE( testTestApi23->getPropInt() == 0 );
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testTestApi23->setPropFloat(0.0f);
        REQUIRE( testTestApi23->getPropFloat() == Approx( 0.0f ) );
    }
    SECTION("Test property propString") {
        // Do implement test here
        testTestApi23->setPropString(std::string());
        REQUIRE( testTestApi23->getPropString() == std::string() );
    }
}
