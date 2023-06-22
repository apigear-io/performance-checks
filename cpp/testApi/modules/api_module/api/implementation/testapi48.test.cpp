#include <memory>
#include "catch2/catch.hpp"
#include "api/implementation/testapi48.h"

using namespace Cpp::Api;
TEST_CASE("Testing TestApi48", "[TestApi48]"){
    std::unique_ptr<ITestApi48> testTestApi48 = std::make_unique<TestApi48>();
    // setup your test
    SECTION("Test operation funcInt") {
        // Do implement test here
        testTestApi48->funcInt(0);
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testTestApi48->funcFloat(0.0f);
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testTestApi48->funcString(std::string());
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testTestApi48->setPropInt(0);
        REQUIRE( testTestApi48->getPropInt() == 0 );
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testTestApi48->setPropFloat(0.0f);
        REQUIRE( testTestApi48->getPropFloat() == Approx( 0.0f ) );
    }
    SECTION("Test property propString") {
        // Do implement test here
        testTestApi48->setPropString(std::string());
        REQUIRE( testTestApi48->getPropString() == std::string() );
    }
}
