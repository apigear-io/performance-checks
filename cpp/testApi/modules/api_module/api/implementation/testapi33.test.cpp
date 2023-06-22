#include <memory>
#include "catch2/catch.hpp"
#include "api/implementation/testapi33.h"

using namespace Cpp::Api;
TEST_CASE("Testing TestApi33", "[TestApi33]"){
    std::unique_ptr<ITestApi33> testTestApi33 = std::make_unique<TestApi33>();
    // setup your test
    SECTION("Test operation funcInt") {
        // Do implement test here
        testTestApi33->funcInt(0);
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testTestApi33->funcFloat(0.0f);
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testTestApi33->funcString(std::string());
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testTestApi33->setPropInt(0);
        REQUIRE( testTestApi33->getPropInt() == 0 );
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testTestApi33->setPropFloat(0.0f);
        REQUIRE( testTestApi33->getPropFloat() == Approx( 0.0f ) );
    }
    SECTION("Test property propString") {
        // Do implement test here
        testTestApi33->setPropString(std::string());
        REQUIRE( testTestApi33->getPropString() == std::string() );
    }
}
