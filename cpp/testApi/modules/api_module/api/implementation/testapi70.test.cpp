#include <memory>
#include "catch2/catch.hpp"
#include "api/implementation/testapi70.h"

using namespace Cpp::Api;
TEST_CASE("Testing TestApi70", "[TestApi70]"){
    std::unique_ptr<ITestApi70> testTestApi70 = std::make_unique<TestApi70>();
    // setup your test
    SECTION("Test operation funcInt") {
        // Do implement test here
        testTestApi70->funcInt(0);
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testTestApi70->funcFloat(0.0f);
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testTestApi70->funcString(std::string());
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testTestApi70->setPropInt(0);
        REQUIRE( testTestApi70->getPropInt() == 0 );
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testTestApi70->setPropFloat(0.0f);
        REQUIRE( testTestApi70->getPropFloat() == Approx( 0.0f ) );
    }
    SECTION("Test property propString") {
        // Do implement test here
        testTestApi70->setPropString(std::string());
        REQUIRE( testTestApi70->getPropString() == std::string() );
    }
}
