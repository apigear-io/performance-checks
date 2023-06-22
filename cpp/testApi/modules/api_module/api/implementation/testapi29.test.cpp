#include <memory>
#include "catch2/catch.hpp"
#include "api/implementation/testapi29.h"

using namespace Cpp::Api;
TEST_CASE("Testing TestApi29", "[TestApi29]"){
    std::unique_ptr<ITestApi29> testTestApi29 = std::make_unique<TestApi29>();
    // setup your test
    SECTION("Test operation funcInt") {
        // Do implement test here
        testTestApi29->funcInt(0);
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testTestApi29->funcFloat(0.0f);
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testTestApi29->funcString(std::string());
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testTestApi29->setPropInt(0);
        REQUIRE( testTestApi29->getPropInt() == 0 );
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testTestApi29->setPropFloat(0.0f);
        REQUIRE( testTestApi29->getPropFloat() == Approx( 0.0f ) );
    }
    SECTION("Test property propString") {
        // Do implement test here
        testTestApi29->setPropString(std::string());
        REQUIRE( testTestApi29->getPropString() == std::string() );
    }
}
