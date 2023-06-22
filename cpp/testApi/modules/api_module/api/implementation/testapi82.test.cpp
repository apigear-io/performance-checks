#include <memory>
#include "catch2/catch.hpp"
#include "api/implementation/testapi82.h"

using namespace Cpp::Api;
TEST_CASE("Testing TestApi82", "[TestApi82]"){
    std::unique_ptr<ITestApi82> testTestApi82 = std::make_unique<TestApi82>();
    // setup your test
    SECTION("Test operation funcInt") {
        // Do implement test here
        testTestApi82->funcInt(0);
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testTestApi82->funcFloat(0.0f);
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testTestApi82->funcString(std::string());
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testTestApi82->setPropInt(0);
        REQUIRE( testTestApi82->getPropInt() == 0 );
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testTestApi82->setPropFloat(0.0f);
        REQUIRE( testTestApi82->getPropFloat() == Approx( 0.0f ) );
    }
    SECTION("Test property propString") {
        // Do implement test here
        testTestApi82->setPropString(std::string());
        REQUIRE( testTestApi82->getPropString() == std::string() );
    }
}
