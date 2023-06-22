#include <memory>
#include "catch2/catch.hpp"
#include "api/implementation/testapi10.h"

using namespace Cpp::Api;
TEST_CASE("Testing TestApi10", "[TestApi10]"){
    std::unique_ptr<ITestApi10> testTestApi10 = std::make_unique<TestApi10>();
    // setup your test
    SECTION("Test operation funcInt") {
        // Do implement test here
        testTestApi10->funcInt(0);
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testTestApi10->funcFloat(0.0f);
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testTestApi10->funcString(std::string());
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testTestApi10->setPropInt(0);
        REQUIRE( testTestApi10->getPropInt() == 0 );
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testTestApi10->setPropFloat(0.0f);
        REQUIRE( testTestApi10->getPropFloat() == Approx( 0.0f ) );
    }
    SECTION("Test property propString") {
        // Do implement test here
        testTestApi10->setPropString(std::string());
        REQUIRE( testTestApi10->getPropString() == std::string() );
    }
}
