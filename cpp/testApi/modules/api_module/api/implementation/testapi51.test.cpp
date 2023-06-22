#include <memory>
#include "catch2/catch.hpp"
#include "api/implementation/testapi51.h"

using namespace Cpp::Api;
TEST_CASE("Testing TestApi51", "[TestApi51]"){
    std::unique_ptr<ITestApi51> testTestApi51 = std::make_unique<TestApi51>();
    // setup your test
    SECTION("Test operation funcInt") {
        // Do implement test here
        testTestApi51->funcInt(0);
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testTestApi51->funcFloat(0.0f);
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testTestApi51->funcString(std::string());
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testTestApi51->setPropInt(0);
        REQUIRE( testTestApi51->getPropInt() == 0 );
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testTestApi51->setPropFloat(0.0f);
        REQUIRE( testTestApi51->getPropFloat() == Approx( 0.0f ) );
    }
    SECTION("Test property propString") {
        // Do implement test here
        testTestApi51->setPropString(std::string());
        REQUIRE( testTestApi51->getPropString() == std::string() );
    }
}
