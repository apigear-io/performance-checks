#include <memory>
#include "catch2/catch.hpp"
#include "api/implementation/testapi26.h"

using namespace Cpp::Api;
TEST_CASE("Testing TestApi26", "[TestApi26]"){
    std::unique_ptr<ITestApi26> testTestApi26 = std::make_unique<TestApi26>();
    // setup your test
    SECTION("Test operation funcInt") {
        // Do implement test here
        testTestApi26->funcInt(0);
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testTestApi26->funcFloat(0.0f);
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testTestApi26->funcString(std::string());
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testTestApi26->setPropInt(0);
        REQUIRE( testTestApi26->getPropInt() == 0 );
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testTestApi26->setPropFloat(0.0f);
        REQUIRE( testTestApi26->getPropFloat() == Approx( 0.0f ) );
    }
    SECTION("Test property propString") {
        // Do implement test here
        testTestApi26->setPropString(std::string());
        REQUIRE( testTestApi26->getPropString() == std::string() );
    }
}
