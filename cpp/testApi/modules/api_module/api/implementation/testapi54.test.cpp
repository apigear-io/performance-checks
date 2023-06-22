#include <memory>
#include "catch2/catch.hpp"
#include "api/implementation/testapi54.h"

using namespace Cpp::Api;
TEST_CASE("Testing TestApi54", "[TestApi54]"){
    std::unique_ptr<ITestApi54> testTestApi54 = std::make_unique<TestApi54>();
    // setup your test
    SECTION("Test operation funcInt") {
        // Do implement test here
        testTestApi54->funcInt(0);
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testTestApi54->funcFloat(0.0f);
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testTestApi54->funcString(std::string());
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testTestApi54->setPropInt(0);
        REQUIRE( testTestApi54->getPropInt() == 0 );
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testTestApi54->setPropFloat(0.0f);
        REQUIRE( testTestApi54->getPropFloat() == Approx( 0.0f ) );
    }
    SECTION("Test property propString") {
        // Do implement test here
        testTestApi54->setPropString(std::string());
        REQUIRE( testTestApi54->getPropString() == std::string() );
    }
}
