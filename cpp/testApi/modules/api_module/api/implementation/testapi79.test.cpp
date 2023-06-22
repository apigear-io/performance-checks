#include <memory>
#include "catch2/catch.hpp"
#include "api/implementation/testapi79.h"

using namespace Cpp::Api;
TEST_CASE("Testing TestApi79", "[TestApi79]"){
    std::unique_ptr<ITestApi79> testTestApi79 = std::make_unique<TestApi79>();
    // setup your test
    SECTION("Test operation funcInt") {
        // Do implement test here
        testTestApi79->funcInt(0);
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testTestApi79->funcFloat(0.0f);
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testTestApi79->funcString(std::string());
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testTestApi79->setPropInt(0);
        REQUIRE( testTestApi79->getPropInt() == 0 );
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testTestApi79->setPropFloat(0.0f);
        REQUIRE( testTestApi79->getPropFloat() == Approx( 0.0f ) );
    }
    SECTION("Test property propString") {
        // Do implement test here
        testTestApi79->setPropString(std::string());
        REQUIRE( testTestApi79->getPropString() == std::string() );
    }
}
