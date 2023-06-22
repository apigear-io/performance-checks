#include <memory>
#include "catch2/catch.hpp"
#include "api/implementation/testapi4.h"

using namespace Cpp::Api;
TEST_CASE("Testing TestApi4", "[TestApi4]"){
    std::unique_ptr<ITestApi4> testTestApi4 = std::make_unique<TestApi4>();
    // setup your test
    SECTION("Test operation funcInt") {
        // Do implement test here
        testTestApi4->funcInt(0);
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testTestApi4->funcFloat(0.0f);
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testTestApi4->funcString(std::string());
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testTestApi4->setPropInt(0);
        REQUIRE( testTestApi4->getPropInt() == 0 );
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testTestApi4->setPropFloat(0.0f);
        REQUIRE( testTestApi4->getPropFloat() == Approx( 0.0f ) );
    }
    SECTION("Test property propString") {
        // Do implement test here
        testTestApi4->setPropString(std::string());
        REQUIRE( testTestApi4->getPropString() == std::string() );
    }
}
