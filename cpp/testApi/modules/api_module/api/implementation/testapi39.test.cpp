#include <memory>
#include "catch2/catch.hpp"
#include "api/implementation/testapi39.h"

using namespace Cpp::Api;
TEST_CASE("Testing TestApi39", "[TestApi39]"){
    std::unique_ptr<ITestApi39> testTestApi39 = std::make_unique<TestApi39>();
    // setup your test
    SECTION("Test operation funcInt") {
        // Do implement test here
        testTestApi39->funcInt(0);
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testTestApi39->funcFloat(0.0f);
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testTestApi39->funcString(std::string());
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testTestApi39->setPropInt(0);
        REQUIRE( testTestApi39->getPropInt() == 0 );
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testTestApi39->setPropFloat(0.0f);
        REQUIRE( testTestApi39->getPropFloat() == Approx( 0.0f ) );
    }
    SECTION("Test property propString") {
        // Do implement test here
        testTestApi39->setPropString(std::string());
        REQUIRE( testTestApi39->getPropString() == std::string() );
    }
}
