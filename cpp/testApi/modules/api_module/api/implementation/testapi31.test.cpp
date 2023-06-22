#include <memory>
#include "catch2/catch.hpp"
#include "api/implementation/testapi31.h"

using namespace Cpp::Api;
TEST_CASE("Testing TestApi31", "[TestApi31]"){
    std::unique_ptr<ITestApi31> testTestApi31 = std::make_unique<TestApi31>();
    // setup your test
    SECTION("Test operation funcInt") {
        // Do implement test here
        testTestApi31->funcInt(0);
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testTestApi31->funcFloat(0.0f);
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testTestApi31->funcString(std::string());
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testTestApi31->setPropInt(0);
        REQUIRE( testTestApi31->getPropInt() == 0 );
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testTestApi31->setPropFloat(0.0f);
        REQUIRE( testTestApi31->getPropFloat() == Approx( 0.0f ) );
    }
    SECTION("Test property propString") {
        // Do implement test here
        testTestApi31->setPropString(std::string());
        REQUIRE( testTestApi31->getPropString() == std::string() );
    }
}
