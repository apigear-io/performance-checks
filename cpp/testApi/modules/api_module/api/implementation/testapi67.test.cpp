#include <memory>
#include "catch2/catch.hpp"
#include "api/implementation/testapi67.h"

using namespace Cpp::Api;
TEST_CASE("Testing TestApi67", "[TestApi67]"){
    std::unique_ptr<ITestApi67> testTestApi67 = std::make_unique<TestApi67>();
    // setup your test
    SECTION("Test operation funcInt") {
        // Do implement test here
        testTestApi67->funcInt(0);
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testTestApi67->funcFloat(0.0f);
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testTestApi67->funcString(std::string());
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testTestApi67->setPropInt(0);
        REQUIRE( testTestApi67->getPropInt() == 0 );
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testTestApi67->setPropFloat(0.0f);
        REQUIRE( testTestApi67->getPropFloat() == Approx( 0.0f ) );
    }
    SECTION("Test property propString") {
        // Do implement test here
        testTestApi67->setPropString(std::string());
        REQUIRE( testTestApi67->getPropString() == std::string() );
    }
}
