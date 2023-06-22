#include <memory>
#include "catch2/catch.hpp"
#include "api/implementation/testapi56.h"

using namespace Cpp::Api;
TEST_CASE("Testing TestApi56", "[TestApi56]"){
    std::unique_ptr<ITestApi56> testTestApi56 = std::make_unique<TestApi56>();
    // setup your test
    SECTION("Test operation funcInt") {
        // Do implement test here
        testTestApi56->funcInt(0);
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testTestApi56->funcFloat(0.0f);
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testTestApi56->funcString(std::string());
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testTestApi56->setPropInt(0);
        REQUIRE( testTestApi56->getPropInt() == 0 );
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testTestApi56->setPropFloat(0.0f);
        REQUIRE( testTestApi56->getPropFloat() == Approx( 0.0f ) );
    }
    SECTION("Test property propString") {
        // Do implement test here
        testTestApi56->setPropString(std::string());
        REQUIRE( testTestApi56->getPropString() == std::string() );
    }
}
