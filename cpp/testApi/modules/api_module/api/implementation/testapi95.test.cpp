#include <memory>
#include "catch2/catch.hpp"
#include "api/implementation/testapi95.h"

using namespace Cpp::Api;
TEST_CASE("Testing TestApi95", "[TestApi95]"){
    std::unique_ptr<ITestApi95> testTestApi95 = std::make_unique<TestApi95>();
    // setup your test
    SECTION("Test operation funcInt") {
        // Do implement test here
        testTestApi95->funcInt(0);
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testTestApi95->funcFloat(0.0f);
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testTestApi95->funcString(std::string());
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testTestApi95->setPropInt(0);
        REQUIRE( testTestApi95->getPropInt() == 0 );
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testTestApi95->setPropFloat(0.0f);
        REQUIRE( testTestApi95->getPropFloat() == Approx( 0.0f ) );
    }
    SECTION("Test property propString") {
        // Do implement test here
        testTestApi95->setPropString(std::string());
        REQUIRE( testTestApi95->getPropString() == std::string() );
    }
}
