#include <memory>
#include "catch2/catch.hpp"
#include "api/implementation/testapi92.h"

using namespace Cpp::Api;
TEST_CASE("Testing TestApi92", "[TestApi92]"){
    std::unique_ptr<ITestApi92> testTestApi92 = std::make_unique<TestApi92>();
    // setup your test
    SECTION("Test operation funcInt") {
        // Do implement test here
        testTestApi92->funcInt(0);
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testTestApi92->funcFloat(0.0f);
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testTestApi92->funcString(std::string());
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testTestApi92->setPropInt(0);
        REQUIRE( testTestApi92->getPropInt() == 0 );
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testTestApi92->setPropFloat(0.0f);
        REQUIRE( testTestApi92->getPropFloat() == Approx( 0.0f ) );
    }
    SECTION("Test property propString") {
        // Do implement test here
        testTestApi92->setPropString(std::string());
        REQUIRE( testTestApi92->getPropString() == std::string() );
    }
}
