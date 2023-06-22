#include <memory>
#include "catch2/catch.hpp"
#include "api/implementation/testapi57.h"

using namespace Cpp::Api;
TEST_CASE("Testing TestApi57", "[TestApi57]"){
    std::unique_ptr<ITestApi57> testTestApi57 = std::make_unique<TestApi57>();
    // setup your test
    SECTION("Test operation funcInt") {
        // Do implement test here
        testTestApi57->funcInt(0);
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testTestApi57->funcFloat(0.0f);
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testTestApi57->funcString(std::string());
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testTestApi57->setPropInt(0);
        REQUIRE( testTestApi57->getPropInt() == 0 );
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testTestApi57->setPropFloat(0.0f);
        REQUIRE( testTestApi57->getPropFloat() == Approx( 0.0f ) );
    }
    SECTION("Test property propString") {
        // Do implement test here
        testTestApi57->setPropString(std::string());
        REQUIRE( testTestApi57->getPropString() == std::string() );
    }
}
