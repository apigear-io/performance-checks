#include <memory>
#include "catch2/catch.hpp"
#include "api/implementation/testapi41.h"

using namespace Cpp::Api;
TEST_CASE("Testing TestApi41", "[TestApi41]"){
    std::unique_ptr<ITestApi41> testTestApi41 = std::make_unique<TestApi41>();
    // setup your test
    SECTION("Test operation funcInt") {
        // Do implement test here
        testTestApi41->funcInt(0);
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testTestApi41->funcFloat(0.0f);
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testTestApi41->funcString(std::string());
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testTestApi41->setPropInt(0);
        REQUIRE( testTestApi41->getPropInt() == 0 );
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testTestApi41->setPropFloat(0.0f);
        REQUIRE( testTestApi41->getPropFloat() == Approx( 0.0f ) );
    }
    SECTION("Test property propString") {
        // Do implement test here
        testTestApi41->setPropString(std::string());
        REQUIRE( testTestApi41->getPropString() == std::string() );
    }
}
