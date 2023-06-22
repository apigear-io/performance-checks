#include <memory>
#include "catch2/catch.hpp"
#include "api/implementation/testapi65.h"

using namespace Cpp::Api;
TEST_CASE("Testing TestApi65", "[TestApi65]"){
    std::unique_ptr<ITestApi65> testTestApi65 = std::make_unique<TestApi65>();
    // setup your test
    SECTION("Test operation funcInt") {
        // Do implement test here
        testTestApi65->funcInt(0);
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testTestApi65->funcFloat(0.0f);
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testTestApi65->funcString(std::string());
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testTestApi65->setPropInt(0);
        REQUIRE( testTestApi65->getPropInt() == 0 );
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testTestApi65->setPropFloat(0.0f);
        REQUIRE( testTestApi65->getPropFloat() == Approx( 0.0f ) );
    }
    SECTION("Test property propString") {
        // Do implement test here
        testTestApi65->setPropString(std::string());
        REQUIRE( testTestApi65->getPropString() == std::string() );
    }
}
