#include <memory>
#include "catch2/catch.hpp"
#include "api/implementation/testapi49.h"

using namespace Cpp::Api;
TEST_CASE("Testing TestApi49", "[TestApi49]"){
    std::unique_ptr<ITestApi49> testTestApi49 = std::make_unique<TestApi49>();
    // setup your test
    SECTION("Test operation funcInt") {
        // Do implement test here
        testTestApi49->funcInt(0);
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testTestApi49->funcFloat(0.0f);
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testTestApi49->funcString(std::string());
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testTestApi49->setPropInt(0);
        REQUIRE( testTestApi49->getPropInt() == 0 );
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testTestApi49->setPropFloat(0.0f);
        REQUIRE( testTestApi49->getPropFloat() == Approx( 0.0f ) );
    }
    SECTION("Test property propString") {
        // Do implement test here
        testTestApi49->setPropString(std::string());
        REQUIRE( testTestApi49->getPropString() == std::string() );
    }
}
