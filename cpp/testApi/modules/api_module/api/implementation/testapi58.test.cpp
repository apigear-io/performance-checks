#include <memory>
#include "catch2/catch.hpp"
#include "api/implementation/testapi58.h"

using namespace Cpp::Api;
TEST_CASE("Testing TestApi58", "[TestApi58]"){
    std::unique_ptr<ITestApi58> testTestApi58 = std::make_unique<TestApi58>();
    // setup your test
    SECTION("Test operation funcInt") {
        // Do implement test here
        testTestApi58->funcInt(0);
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testTestApi58->funcFloat(0.0f);
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testTestApi58->funcString(std::string());
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testTestApi58->setPropInt(0);
        REQUIRE( testTestApi58->getPropInt() == 0 );
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testTestApi58->setPropFloat(0.0f);
        REQUIRE( testTestApi58->getPropFloat() == Approx( 0.0f ) );
    }
    SECTION("Test property propString") {
        // Do implement test here
        testTestApi58->setPropString(std::string());
        REQUIRE( testTestApi58->getPropString() == std::string() );
    }
}
