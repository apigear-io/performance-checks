#include <memory>
#include "catch2/catch.hpp"
#include "api/implementation/testapi36.h"

using namespace Cpp::Api;
TEST_CASE("Testing TestApi36", "[TestApi36]"){
    std::unique_ptr<ITestApi36> testTestApi36 = std::make_unique<TestApi36>();
    // setup your test
    SECTION("Test operation funcInt") {
        // Do implement test here
        testTestApi36->funcInt(0);
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testTestApi36->funcFloat(0.0f);
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testTestApi36->funcString(std::string());
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testTestApi36->setPropInt(0);
        REQUIRE( testTestApi36->getPropInt() == 0 );
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testTestApi36->setPropFloat(0.0f);
        REQUIRE( testTestApi36->getPropFloat() == Approx( 0.0f ) );
    }
    SECTION("Test property propString") {
        // Do implement test here
        testTestApi36->setPropString(std::string());
        REQUIRE( testTestApi36->getPropString() == std::string() );
    }
}
