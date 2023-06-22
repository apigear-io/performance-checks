#include <memory>
#include "catch2/catch.hpp"
#include "api/implementation/testapi7.h"

using namespace Cpp::Api;
TEST_CASE("Testing TestApi7", "[TestApi7]"){
    std::unique_ptr<ITestApi7> testTestApi7 = std::make_unique<TestApi7>();
    // setup your test
    SECTION("Test operation funcInt") {
        // Do implement test here
        testTestApi7->funcInt(0);
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testTestApi7->funcFloat(0.0f);
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testTestApi7->funcString(std::string());
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testTestApi7->setPropInt(0);
        REQUIRE( testTestApi7->getPropInt() == 0 );
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testTestApi7->setPropFloat(0.0f);
        REQUIRE( testTestApi7->getPropFloat() == Approx( 0.0f ) );
    }
    SECTION("Test property propString") {
        // Do implement test here
        testTestApi7->setPropString(std::string());
        REQUIRE( testTestApi7->getPropString() == std::string() );
    }
}
