#include <memory>
#include "catch2/catch.hpp"
#include "api/implementation/testapi96.h"

using namespace Cpp::Api;
TEST_CASE("Testing TestApi96", "[TestApi96]"){
    std::unique_ptr<ITestApi96> testTestApi96 = std::make_unique<TestApi96>();
    // setup your test
    SECTION("Test operation funcInt") {
        // Do implement test here
        testTestApi96->funcInt(0);
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testTestApi96->funcFloat(0.0f);
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testTestApi96->funcString(std::string());
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testTestApi96->setPropInt(0);
        REQUIRE( testTestApi96->getPropInt() == 0 );
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testTestApi96->setPropFloat(0.0f);
        REQUIRE( testTestApi96->getPropFloat() == Approx( 0.0f ) );
    }
    SECTION("Test property propString") {
        // Do implement test here
        testTestApi96->setPropString(std::string());
        REQUIRE( testTestApi96->getPropString() == std::string() );
    }
}
