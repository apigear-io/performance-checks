#include <memory>
#include "catch2/catch.hpp"
#include "api/implementation/testapi12.h"

using namespace Cpp::Api;
TEST_CASE("Testing TestApi12", "[TestApi12]"){
    std::unique_ptr<ITestApi12> testTestApi12 = std::make_unique<TestApi12>();
    // setup your test
    SECTION("Test operation funcInt") {
        // Do implement test here
        testTestApi12->funcInt(0);
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testTestApi12->funcFloat(0.0f);
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testTestApi12->funcString(std::string());
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testTestApi12->setPropInt(0);
        REQUIRE( testTestApi12->getPropInt() == 0 );
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testTestApi12->setPropFloat(0.0f);
        REQUIRE( testTestApi12->getPropFloat() == Approx( 0.0f ) );
    }
    SECTION("Test property propString") {
        // Do implement test here
        testTestApi12->setPropString(std::string());
        REQUIRE( testTestApi12->getPropString() == std::string() );
    }
}
