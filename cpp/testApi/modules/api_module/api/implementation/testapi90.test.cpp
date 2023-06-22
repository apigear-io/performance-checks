#include <memory>
#include "catch2/catch.hpp"
#include "api/implementation/testapi90.h"

using namespace Cpp::Api;
TEST_CASE("Testing TestApi90", "[TestApi90]"){
    std::unique_ptr<ITestApi90> testTestApi90 = std::make_unique<TestApi90>();
    // setup your test
    SECTION("Test operation funcInt") {
        // Do implement test here
        testTestApi90->funcInt(0);
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testTestApi90->funcFloat(0.0f);
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testTestApi90->funcString(std::string());
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testTestApi90->setPropInt(0);
        REQUIRE( testTestApi90->getPropInt() == 0 );
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testTestApi90->setPropFloat(0.0f);
        REQUIRE( testTestApi90->getPropFloat() == Approx( 0.0f ) );
    }
    SECTION("Test property propString") {
        // Do implement test here
        testTestApi90->setPropString(std::string());
        REQUIRE( testTestApi90->getPropString() == std::string() );
    }
}
