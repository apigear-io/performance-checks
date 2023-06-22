#include <memory>
#include "catch2/catch.hpp"
#include "api/implementation/testapi63.h"

using namespace Cpp::Api;
TEST_CASE("Testing TestApi63", "[TestApi63]"){
    std::unique_ptr<ITestApi63> testTestApi63 = std::make_unique<TestApi63>();
    // setup your test
    SECTION("Test operation funcInt") {
        // Do implement test here
        testTestApi63->funcInt(0);
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testTestApi63->funcFloat(0.0f);
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testTestApi63->funcString(std::string());
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testTestApi63->setPropInt(0);
        REQUIRE( testTestApi63->getPropInt() == 0 );
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testTestApi63->setPropFloat(0.0f);
        REQUIRE( testTestApi63->getPropFloat() == Approx( 0.0f ) );
    }
    SECTION("Test property propString") {
        // Do implement test here
        testTestApi63->setPropString(std::string());
        REQUIRE( testTestApi63->getPropString() == std::string() );
    }
}
