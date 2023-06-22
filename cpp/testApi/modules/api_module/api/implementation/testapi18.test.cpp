#include <memory>
#include "catch2/catch.hpp"
#include "api/implementation/testapi18.h"

using namespace Cpp::Api;
TEST_CASE("Testing TestApi18", "[TestApi18]"){
    std::unique_ptr<ITestApi18> testTestApi18 = std::make_unique<TestApi18>();
    // setup your test
    SECTION("Test operation funcInt") {
        // Do implement test here
        testTestApi18->funcInt(0);
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testTestApi18->funcFloat(0.0f);
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testTestApi18->funcString(std::string());
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testTestApi18->setPropInt(0);
        REQUIRE( testTestApi18->getPropInt() == 0 );
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testTestApi18->setPropFloat(0.0f);
        REQUIRE( testTestApi18->getPropFloat() == Approx( 0.0f ) );
    }
    SECTION("Test property propString") {
        // Do implement test here
        testTestApi18->setPropString(std::string());
        REQUIRE( testTestApi18->getPropString() == std::string() );
    }
}
