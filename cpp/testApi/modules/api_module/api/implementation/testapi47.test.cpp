#include <memory>
#include "catch2/catch.hpp"
#include "api/implementation/testapi47.h"

using namespace Cpp::Api;
TEST_CASE("Testing TestApi47", "[TestApi47]"){
    std::unique_ptr<ITestApi47> testTestApi47 = std::make_unique<TestApi47>();
    // setup your test
    SECTION("Test operation funcInt") {
        // Do implement test here
        testTestApi47->funcInt(0);
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testTestApi47->funcFloat(0.0f);
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testTestApi47->funcString(std::string());
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testTestApi47->setPropInt(0);
        REQUIRE( testTestApi47->getPropInt() == 0 );
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testTestApi47->setPropFloat(0.0f);
        REQUIRE( testTestApi47->getPropFloat() == Approx( 0.0f ) );
    }
    SECTION("Test property propString") {
        // Do implement test here
        testTestApi47->setPropString(std::string());
        REQUIRE( testTestApi47->getPropString() == std::string() );
    }
}
