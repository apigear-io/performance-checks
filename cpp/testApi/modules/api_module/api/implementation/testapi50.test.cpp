#include <memory>
#include "catch2/catch.hpp"
#include "api/implementation/testapi50.h"

using namespace Cpp::Api;
TEST_CASE("Testing TestApi50", "[TestApi50]"){
    std::unique_ptr<ITestApi50> testTestApi50 = std::make_unique<TestApi50>();
    // setup your test
    SECTION("Test operation funcInt") {
        // Do implement test here
        testTestApi50->funcInt(0);
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testTestApi50->funcFloat(0.0f);
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testTestApi50->funcString(std::string());
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testTestApi50->setPropInt(0);
        REQUIRE( testTestApi50->getPropInt() == 0 );
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testTestApi50->setPropFloat(0.0f);
        REQUIRE( testTestApi50->getPropFloat() == Approx( 0.0f ) );
    }
    SECTION("Test property propString") {
        // Do implement test here
        testTestApi50->setPropString(std::string());
        REQUIRE( testTestApi50->getPropString() == std::string() );
    }
}
