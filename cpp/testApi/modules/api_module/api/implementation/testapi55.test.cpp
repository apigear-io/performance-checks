#include <memory>
#include "catch2/catch.hpp"
#include "api/implementation/testapi55.h"

using namespace Cpp::Api;
TEST_CASE("Testing TestApi55", "[TestApi55]"){
    std::unique_ptr<ITestApi55> testTestApi55 = std::make_unique<TestApi55>();
    // setup your test
    SECTION("Test operation funcInt") {
        // Do implement test here
        testTestApi55->funcInt(0);
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testTestApi55->funcFloat(0.0f);
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testTestApi55->funcString(std::string());
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testTestApi55->setPropInt(0);
        REQUIRE( testTestApi55->getPropInt() == 0 );
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testTestApi55->setPropFloat(0.0f);
        REQUIRE( testTestApi55->getPropFloat() == Approx( 0.0f ) );
    }
    SECTION("Test property propString") {
        // Do implement test here
        testTestApi55->setPropString(std::string());
        REQUIRE( testTestApi55->getPropString() == std::string() );
    }
}
