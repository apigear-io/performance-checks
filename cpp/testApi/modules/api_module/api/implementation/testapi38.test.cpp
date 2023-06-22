#include <memory>
#include "catch2/catch.hpp"
#include "api/implementation/testapi38.h"

using namespace Cpp::Api;
TEST_CASE("Testing TestApi38", "[TestApi38]"){
    std::unique_ptr<ITestApi38> testTestApi38 = std::make_unique<TestApi38>();
    // setup your test
    SECTION("Test operation funcInt") {
        // Do implement test here
        testTestApi38->funcInt(0);
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testTestApi38->funcFloat(0.0f);
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testTestApi38->funcString(std::string());
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testTestApi38->setPropInt(0);
        REQUIRE( testTestApi38->getPropInt() == 0 );
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testTestApi38->setPropFloat(0.0f);
        REQUIRE( testTestApi38->getPropFloat() == Approx( 0.0f ) );
    }
    SECTION("Test property propString") {
        // Do implement test here
        testTestApi38->setPropString(std::string());
        REQUIRE( testTestApi38->getPropString() == std::string() );
    }
}
