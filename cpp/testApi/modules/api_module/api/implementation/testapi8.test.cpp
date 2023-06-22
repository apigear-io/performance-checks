#include <memory>
#include "catch2/catch.hpp"
#include "api/implementation/testapi8.h"

using namespace Cpp::Api;
TEST_CASE("Testing TestApi8", "[TestApi8]"){
    std::unique_ptr<ITestApi8> testTestApi8 = std::make_unique<TestApi8>();
    // setup your test
    SECTION("Test operation funcInt") {
        // Do implement test here
        testTestApi8->funcInt(0);
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testTestApi8->funcFloat(0.0f);
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testTestApi8->funcString(std::string());
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testTestApi8->setPropInt(0);
        REQUIRE( testTestApi8->getPropInt() == 0 );
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testTestApi8->setPropFloat(0.0f);
        REQUIRE( testTestApi8->getPropFloat() == Approx( 0.0f ) );
    }
    SECTION("Test property propString") {
        // Do implement test here
        testTestApi8->setPropString(std::string());
        REQUIRE( testTestApi8->getPropString() == std::string() );
    }
}
