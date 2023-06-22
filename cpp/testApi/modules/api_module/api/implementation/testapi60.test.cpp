#include <memory>
#include "catch2/catch.hpp"
#include "api/implementation/testapi60.h"

using namespace Cpp::Api;
TEST_CASE("Testing TestApi60", "[TestApi60]"){
    std::unique_ptr<ITestApi60> testTestApi60 = std::make_unique<TestApi60>();
    // setup your test
    SECTION("Test operation funcInt") {
        // Do implement test here
        testTestApi60->funcInt(0);
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testTestApi60->funcFloat(0.0f);
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testTestApi60->funcString(std::string());
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testTestApi60->setPropInt(0);
        REQUIRE( testTestApi60->getPropInt() == 0 );
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testTestApi60->setPropFloat(0.0f);
        REQUIRE( testTestApi60->getPropFloat() == Approx( 0.0f ) );
    }
    SECTION("Test property propString") {
        // Do implement test here
        testTestApi60->setPropString(std::string());
        REQUIRE( testTestApi60->getPropString() == std::string() );
    }
}
