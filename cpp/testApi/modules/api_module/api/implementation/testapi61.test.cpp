#include <memory>
#include "catch2/catch.hpp"
#include "api/implementation/testapi61.h"

using namespace Cpp::Api;
TEST_CASE("Testing TestApi61", "[TestApi61]"){
    std::unique_ptr<ITestApi61> testTestApi61 = std::make_unique<TestApi61>();
    // setup your test
    SECTION("Test operation funcInt") {
        // Do implement test here
        testTestApi61->funcInt(0);
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testTestApi61->funcFloat(0.0f);
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testTestApi61->funcString(std::string());
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testTestApi61->setPropInt(0);
        REQUIRE( testTestApi61->getPropInt() == 0 );
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testTestApi61->setPropFloat(0.0f);
        REQUIRE( testTestApi61->getPropFloat() == Approx( 0.0f ) );
    }
    SECTION("Test property propString") {
        // Do implement test here
        testTestApi61->setPropString(std::string());
        REQUIRE( testTestApi61->getPropString() == std::string() );
    }
}
