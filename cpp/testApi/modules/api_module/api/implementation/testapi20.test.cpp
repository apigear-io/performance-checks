#include <memory>
#include "catch2/catch.hpp"
#include "api/implementation/testapi20.h"

using namespace Cpp::Api;
TEST_CASE("Testing TestApi20", "[TestApi20]"){
    std::unique_ptr<ITestApi20> testTestApi20 = std::make_unique<TestApi20>();
    // setup your test
    SECTION("Test operation funcInt") {
        // Do implement test here
        testTestApi20->funcInt(0);
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testTestApi20->funcFloat(0.0f);
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testTestApi20->funcString(std::string());
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testTestApi20->setPropInt(0);
        REQUIRE( testTestApi20->getPropInt() == 0 );
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testTestApi20->setPropFloat(0.0f);
        REQUIRE( testTestApi20->getPropFloat() == Approx( 0.0f ) );
    }
    SECTION("Test property propString") {
        // Do implement test here
        testTestApi20->setPropString(std::string());
        REQUIRE( testTestApi20->getPropString() == std::string() );
    }
}
