#include <memory>
#include "catch2/catch.hpp"
#include "api/implementation/testapi43.h"

using namespace Cpp::Api;
TEST_CASE("Testing TestApi43", "[TestApi43]"){
    std::unique_ptr<ITestApi43> testTestApi43 = std::make_unique<TestApi43>();
    // setup your test
    SECTION("Test operation funcInt") {
        // Do implement test here
        testTestApi43->funcInt(0);
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testTestApi43->funcFloat(0.0f);
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testTestApi43->funcString(std::string());
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testTestApi43->setPropInt(0);
        REQUIRE( testTestApi43->getPropInt() == 0 );
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testTestApi43->setPropFloat(0.0f);
        REQUIRE( testTestApi43->getPropFloat() == Approx( 0.0f ) );
    }
    SECTION("Test property propString") {
        // Do implement test here
        testTestApi43->setPropString(std::string());
        REQUIRE( testTestApi43->getPropString() == std::string() );
    }
}
