#include <memory>
#include "catch2/catch.hpp"
#include "api/implementation/testapi42.h"

using namespace Cpp::Api;
TEST_CASE("Testing TestApi42", "[TestApi42]"){
    std::unique_ptr<ITestApi42> testTestApi42 = std::make_unique<TestApi42>();
    // setup your test
    SECTION("Test operation funcInt") {
        // Do implement test here
        testTestApi42->funcInt(0);
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testTestApi42->funcFloat(0.0f);
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testTestApi42->funcString(std::string());
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testTestApi42->setPropInt(0);
        REQUIRE( testTestApi42->getPropInt() == 0 );
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testTestApi42->setPropFloat(0.0f);
        REQUIRE( testTestApi42->getPropFloat() == Approx( 0.0f ) );
    }
    SECTION("Test property propString") {
        // Do implement test here
        testTestApi42->setPropString(std::string());
        REQUIRE( testTestApi42->getPropString() == std::string() );
    }
}
