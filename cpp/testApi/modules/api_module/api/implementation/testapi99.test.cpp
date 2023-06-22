#include <memory>
#include "catch2/catch.hpp"
#include "api/implementation/testapi99.h"

using namespace Cpp::Api;
TEST_CASE("Testing TestApi99", "[TestApi99]"){
    std::unique_ptr<ITestApi99> testTestApi99 = std::make_unique<TestApi99>();
    // setup your test
    SECTION("Test operation funcInt") {
        // Do implement test here
        testTestApi99->funcInt(0);
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testTestApi99->funcFloat(0.0f);
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testTestApi99->funcString(std::string());
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testTestApi99->setPropInt(0);
        REQUIRE( testTestApi99->getPropInt() == 0 );
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testTestApi99->setPropFloat(0.0f);
        REQUIRE( testTestApi99->getPropFloat() == Approx( 0.0f ) );
    }
    SECTION("Test property propString") {
        // Do implement test here
        testTestApi99->setPropString(std::string());
        REQUIRE( testTestApi99->getPropString() == std::string() );
    }
}
