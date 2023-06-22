#include <memory>
#include "catch2/catch.hpp"
#include "api/implementation/testapi5.h"

using namespace Cpp::Api;
TEST_CASE("Testing TestApi5", "[TestApi5]"){
    std::unique_ptr<ITestApi5> testTestApi5 = std::make_unique<TestApi5>();
    // setup your test
    SECTION("Test operation funcInt") {
        // Do implement test here
        testTestApi5->funcInt(0);
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testTestApi5->funcFloat(0.0f);
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testTestApi5->funcString(std::string());
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testTestApi5->setPropInt(0);
        REQUIRE( testTestApi5->getPropInt() == 0 );
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testTestApi5->setPropFloat(0.0f);
        REQUIRE( testTestApi5->getPropFloat() == Approx( 0.0f ) );
    }
    SECTION("Test property propString") {
        // Do implement test here
        testTestApi5->setPropString(std::string());
        REQUIRE( testTestApi5->getPropString() == std::string() );
    }
}
