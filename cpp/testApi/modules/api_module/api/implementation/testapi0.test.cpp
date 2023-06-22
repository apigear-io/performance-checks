#include <memory>
#include "catch2/catch.hpp"
#include "api/implementation/testapi0.h"

using namespace Cpp::Api;
TEST_CASE("Testing TestApi0", "[TestApi0]"){
    std::unique_ptr<ITestApi0> testTestApi0 = std::make_unique<TestApi0>();
    // setup your test
    SECTION("Test operation funcInt") {
        // Do implement test here
        testTestApi0->funcInt(0);
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testTestApi0->funcFloat(0.0f);
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testTestApi0->funcString(std::string());
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testTestApi0->setPropInt(0);
        REQUIRE( testTestApi0->getPropInt() == 0 );
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testTestApi0->setPropFloat(0.0f);
        REQUIRE( testTestApi0->getPropFloat() == Approx( 0.0f ) );
    }
    SECTION("Test property propString") {
        // Do implement test here
        testTestApi0->setPropString(std::string());
        REQUIRE( testTestApi0->getPropString() == std::string() );
    }
}
