#include <memory>
#include "catch2/catch.hpp"
#include "api/implementation/testapi72.h"

using namespace Cpp::Api;
TEST_CASE("Testing TestApi72", "[TestApi72]"){
    std::unique_ptr<ITestApi72> testTestApi72 = std::make_unique<TestApi72>();
    // setup your test
    SECTION("Test operation funcInt") {
        // Do implement test here
        testTestApi72->funcInt(0);
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testTestApi72->funcFloat(0.0f);
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testTestApi72->funcString(std::string());
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testTestApi72->setPropInt(0);
        REQUIRE( testTestApi72->getPropInt() == 0 );
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testTestApi72->setPropFloat(0.0f);
        REQUIRE( testTestApi72->getPropFloat() == Approx( 0.0f ) );
    }
    SECTION("Test property propString") {
        // Do implement test here
        testTestApi72->setPropString(std::string());
        REQUIRE( testTestApi72->getPropString() == std::string() );
    }
}
