#include <memory>
#include "catch2/catch.hpp"
#include "api/implementation/testapi76.h"

using namespace Cpp::Api;
TEST_CASE("Testing TestApi76", "[TestApi76]"){
    std::unique_ptr<ITestApi76> testTestApi76 = std::make_unique<TestApi76>();
    // setup your test
    SECTION("Test operation funcInt") {
        // Do implement test here
        testTestApi76->funcInt(0);
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testTestApi76->funcFloat(0.0f);
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testTestApi76->funcString(std::string());
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testTestApi76->setPropInt(0);
        REQUIRE( testTestApi76->getPropInt() == 0 );
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testTestApi76->setPropFloat(0.0f);
        REQUIRE( testTestApi76->getPropFloat() == Approx( 0.0f ) );
    }
    SECTION("Test property propString") {
        // Do implement test here
        testTestApi76->setPropString(std::string());
        REQUIRE( testTestApi76->getPropString() == std::string() );
    }
}
