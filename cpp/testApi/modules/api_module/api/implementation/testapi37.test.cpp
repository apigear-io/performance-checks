#include <memory>
#include "catch2/catch.hpp"
#include "api/implementation/testapi37.h"

using namespace Cpp::Api;
TEST_CASE("Testing TestApi37", "[TestApi37]"){
    std::unique_ptr<ITestApi37> testTestApi37 = std::make_unique<TestApi37>();
    // setup your test
    SECTION("Test operation funcInt") {
        // Do implement test here
        testTestApi37->funcInt(0);
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testTestApi37->funcFloat(0.0f);
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testTestApi37->funcString(std::string());
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testTestApi37->setPropInt(0);
        REQUIRE( testTestApi37->getPropInt() == 0 );
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testTestApi37->setPropFloat(0.0f);
        REQUIRE( testTestApi37->getPropFloat() == Approx( 0.0f ) );
    }
    SECTION("Test property propString") {
        // Do implement test here
        testTestApi37->setPropString(std::string());
        REQUIRE( testTestApi37->getPropString() == std::string() );
    }
}
