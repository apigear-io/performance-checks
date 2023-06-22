#include <memory>
#include "catch2/catch.hpp"
#include "api/implementation/testapi13.h"

using namespace Cpp::Api;
TEST_CASE("Testing TestApi13", "[TestApi13]"){
    std::unique_ptr<ITestApi13> testTestApi13 = std::make_unique<TestApi13>();
    // setup your test
    SECTION("Test operation funcInt") {
        // Do implement test here
        testTestApi13->funcInt(0);
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testTestApi13->funcFloat(0.0f);
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testTestApi13->funcString(std::string());
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testTestApi13->setPropInt(0);
        REQUIRE( testTestApi13->getPropInt() == 0 );
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testTestApi13->setPropFloat(0.0f);
        REQUIRE( testTestApi13->getPropFloat() == Approx( 0.0f ) );
    }
    SECTION("Test property propString") {
        // Do implement test here
        testTestApi13->setPropString(std::string());
        REQUIRE( testTestApi13->getPropString() == std::string() );
    }
}
