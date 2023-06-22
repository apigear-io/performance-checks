#include <memory>
#include "catch2/catch.hpp"
#include "api/implementation/testapi69.h"

using namespace Cpp::Api;
TEST_CASE("Testing TestApi69", "[TestApi69]"){
    std::unique_ptr<ITestApi69> testTestApi69 = std::make_unique<TestApi69>();
    // setup your test
    SECTION("Test operation funcInt") {
        // Do implement test here
        testTestApi69->funcInt(0);
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testTestApi69->funcFloat(0.0f);
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testTestApi69->funcString(std::string());
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testTestApi69->setPropInt(0);
        REQUIRE( testTestApi69->getPropInt() == 0 );
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testTestApi69->setPropFloat(0.0f);
        REQUIRE( testTestApi69->getPropFloat() == Approx( 0.0f ) );
    }
    SECTION("Test property propString") {
        // Do implement test here
        testTestApi69->setPropString(std::string());
        REQUIRE( testTestApi69->getPropString() == std::string() );
    }
}
