#include <memory>
#include "catch2/catch.hpp"
#include "api/implementation/testapi44.h"

using namespace Cpp::Api;
TEST_CASE("Testing TestApi44", "[TestApi44]"){
    std::unique_ptr<ITestApi44> testTestApi44 = std::make_unique<TestApi44>();
    // setup your test
    SECTION("Test operation funcInt") {
        // Do implement test here
        testTestApi44->funcInt(0);
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testTestApi44->funcFloat(0.0f);
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testTestApi44->funcString(std::string());
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testTestApi44->setPropInt(0);
        REQUIRE( testTestApi44->getPropInt() == 0 );
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testTestApi44->setPropFloat(0.0f);
        REQUIRE( testTestApi44->getPropFloat() == Approx( 0.0f ) );
    }
    SECTION("Test property propString") {
        // Do implement test here
        testTestApi44->setPropString(std::string());
        REQUIRE( testTestApi44->getPropString() == std::string() );
    }
}
