#include <memory>
#include "catch2/catch.hpp"
#include "api/implementation/testapi53.h"

using namespace Cpp::Api;
TEST_CASE("Testing TestApi53", "[TestApi53]"){
    std::unique_ptr<ITestApi53> testTestApi53 = std::make_unique<TestApi53>();
    // setup your test
    SECTION("Test operation funcInt") {
        // Do implement test here
        testTestApi53->funcInt(0);
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testTestApi53->funcFloat(0.0f);
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testTestApi53->funcString(std::string());
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testTestApi53->setPropInt(0);
        REQUIRE( testTestApi53->getPropInt() == 0 );
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testTestApi53->setPropFloat(0.0f);
        REQUIRE( testTestApi53->getPropFloat() == Approx( 0.0f ) );
    }
    SECTION("Test property propString") {
        // Do implement test here
        testTestApi53->setPropString(std::string());
        REQUIRE( testTestApi53->getPropString() == std::string() );
    }
}
