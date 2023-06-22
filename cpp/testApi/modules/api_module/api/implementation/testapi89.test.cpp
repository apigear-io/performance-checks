#include <memory>
#include "catch2/catch.hpp"
#include "api/implementation/testapi89.h"

using namespace Cpp::Api;
TEST_CASE("Testing TestApi89", "[TestApi89]"){
    std::unique_ptr<ITestApi89> testTestApi89 = std::make_unique<TestApi89>();
    // setup your test
    SECTION("Test operation funcInt") {
        // Do implement test here
        testTestApi89->funcInt(0);
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testTestApi89->funcFloat(0.0f);
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testTestApi89->funcString(std::string());
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testTestApi89->setPropInt(0);
        REQUIRE( testTestApi89->getPropInt() == 0 );
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testTestApi89->setPropFloat(0.0f);
        REQUIRE( testTestApi89->getPropFloat() == Approx( 0.0f ) );
    }
    SECTION("Test property propString") {
        // Do implement test here
        testTestApi89->setPropString(std::string());
        REQUIRE( testTestApi89->getPropString() == std::string() );
    }
}
