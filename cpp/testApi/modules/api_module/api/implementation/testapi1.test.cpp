#include <memory>
#include "catch2/catch.hpp"
#include "api/implementation/testapi1.h"

using namespace Cpp::Api;
TEST_CASE("Testing TestApi1", "[TestApi1]"){
    std::unique_ptr<ITestApi1> testTestApi1 = std::make_unique<TestApi1>();
    // setup your test
    SECTION("Test operation funcInt") {
        // Do implement test here
        testTestApi1->funcInt(0);
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testTestApi1->funcFloat(0.0f);
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testTestApi1->funcString(std::string());
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testTestApi1->setPropInt(0);
        REQUIRE( testTestApi1->getPropInt() == 0 );
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testTestApi1->setPropFloat(0.0f);
        REQUIRE( testTestApi1->getPropFloat() == Approx( 0.0f ) );
    }
    SECTION("Test property propString") {
        // Do implement test here
        testTestApi1->setPropString(std::string());
        REQUIRE( testTestApi1->getPropString() == std::string() );
    }
}
