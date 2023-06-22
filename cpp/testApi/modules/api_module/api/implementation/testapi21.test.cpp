#include <memory>
#include "catch2/catch.hpp"
#include "api/implementation/testapi21.h"

using namespace Cpp::Api;
TEST_CASE("Testing TestApi21", "[TestApi21]"){
    std::unique_ptr<ITestApi21> testTestApi21 = std::make_unique<TestApi21>();
    // setup your test
    SECTION("Test operation funcInt") {
        // Do implement test here
        testTestApi21->funcInt(0);
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testTestApi21->funcFloat(0.0f);
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testTestApi21->funcString(std::string());
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testTestApi21->setPropInt(0);
        REQUIRE( testTestApi21->getPropInt() == 0 );
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testTestApi21->setPropFloat(0.0f);
        REQUIRE( testTestApi21->getPropFloat() == Approx( 0.0f ) );
    }
    SECTION("Test property propString") {
        // Do implement test here
        testTestApi21->setPropString(std::string());
        REQUIRE( testTestApi21->getPropString() == std::string() );
    }
}
