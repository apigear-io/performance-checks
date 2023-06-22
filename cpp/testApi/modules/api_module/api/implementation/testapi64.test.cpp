#include <memory>
#include "catch2/catch.hpp"
#include "api/implementation/testapi64.h"

using namespace Cpp::Api;
TEST_CASE("Testing TestApi64", "[TestApi64]"){
    std::unique_ptr<ITestApi64> testTestApi64 = std::make_unique<TestApi64>();
    // setup your test
    SECTION("Test operation funcInt") {
        // Do implement test here
        testTestApi64->funcInt(0);
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testTestApi64->funcFloat(0.0f);
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testTestApi64->funcString(std::string());
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testTestApi64->setPropInt(0);
        REQUIRE( testTestApi64->getPropInt() == 0 );
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testTestApi64->setPropFloat(0.0f);
        REQUIRE( testTestApi64->getPropFloat() == Approx( 0.0f ) );
    }
    SECTION("Test property propString") {
        // Do implement test here
        testTestApi64->setPropString(std::string());
        REQUIRE( testTestApi64->getPropString() == std::string() );
    }
}
