#include <memory>
#include "catch2/catch.hpp"
#include "api/implementation/testapi93.h"

using namespace Cpp::Api;
TEST_CASE("Testing TestApi93", "[TestApi93]"){
    std::unique_ptr<ITestApi93> testTestApi93 = std::make_unique<TestApi93>();
    // setup your test
    SECTION("Test operation funcInt") {
        // Do implement test here
        testTestApi93->funcInt(0);
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testTestApi93->funcFloat(0.0f);
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testTestApi93->funcString(std::string());
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testTestApi93->setPropInt(0);
        REQUIRE( testTestApi93->getPropInt() == 0 );
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testTestApi93->setPropFloat(0.0f);
        REQUIRE( testTestApi93->getPropFloat() == Approx( 0.0f ) );
    }
    SECTION("Test property propString") {
        // Do implement test here
        testTestApi93->setPropString(std::string());
        REQUIRE( testTestApi93->getPropString() == std::string() );
    }
}
