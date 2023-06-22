#include <memory>
#include "catch2/catch.hpp"
#include "api/implementation/testapi78.h"

using namespace Cpp::Api;
TEST_CASE("Testing TestApi78", "[TestApi78]"){
    std::unique_ptr<ITestApi78> testTestApi78 = std::make_unique<TestApi78>();
    // setup your test
    SECTION("Test operation funcInt") {
        // Do implement test here
        testTestApi78->funcInt(0);
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testTestApi78->funcFloat(0.0f);
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testTestApi78->funcString(std::string());
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testTestApi78->setPropInt(0);
        REQUIRE( testTestApi78->getPropInt() == 0 );
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testTestApi78->setPropFloat(0.0f);
        REQUIRE( testTestApi78->getPropFloat() == Approx( 0.0f ) );
    }
    SECTION("Test property propString") {
        // Do implement test here
        testTestApi78->setPropString(std::string());
        REQUIRE( testTestApi78->getPropString() == std::string() );
    }
}
