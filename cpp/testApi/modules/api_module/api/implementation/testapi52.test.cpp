#include <memory>
#include "catch2/catch.hpp"
#include "api/implementation/testapi52.h"

using namespace Cpp::Api;
TEST_CASE("Testing TestApi52", "[TestApi52]"){
    std::unique_ptr<ITestApi52> testTestApi52 = std::make_unique<TestApi52>();
    // setup your test
    SECTION("Test operation funcInt") {
        // Do implement test here
        testTestApi52->funcInt(0);
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testTestApi52->funcFloat(0.0f);
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testTestApi52->funcString(std::string());
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testTestApi52->setPropInt(0);
        REQUIRE( testTestApi52->getPropInt() == 0 );
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testTestApi52->setPropFloat(0.0f);
        REQUIRE( testTestApi52->getPropFloat() == Approx( 0.0f ) );
    }
    SECTION("Test property propString") {
        // Do implement test here
        testTestApi52->setPropString(std::string());
        REQUIRE( testTestApi52->getPropString() == std::string() );
    }
}
