#include <memory>
#include "catch2/catch.hpp"
#include "api/implementation/testapi97.h"

using namespace Cpp::Api;
TEST_CASE("Testing TestApi97", "[TestApi97]"){
    std::unique_ptr<ITestApi97> testTestApi97 = std::make_unique<TestApi97>();
    // setup your test
    SECTION("Test operation funcInt") {
        // Do implement test here
        testTestApi97->funcInt(0);
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testTestApi97->funcFloat(0.0f);
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testTestApi97->funcString(std::string());
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testTestApi97->setPropInt(0);
        REQUIRE( testTestApi97->getPropInt() == 0 );
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testTestApi97->setPropFloat(0.0f);
        REQUIRE( testTestApi97->getPropFloat() == Approx( 0.0f ) );
    }
    SECTION("Test property propString") {
        // Do implement test here
        testTestApi97->setPropString(std::string());
        REQUIRE( testTestApi97->getPropString() == std::string() );
    }
}
