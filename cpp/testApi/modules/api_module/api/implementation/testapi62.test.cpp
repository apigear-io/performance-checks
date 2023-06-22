#include <memory>
#include "catch2/catch.hpp"
#include "api/implementation/testapi62.h"

using namespace Cpp::Api;
TEST_CASE("Testing TestApi62", "[TestApi62]"){
    std::unique_ptr<ITestApi62> testTestApi62 = std::make_unique<TestApi62>();
    // setup your test
    SECTION("Test operation funcInt") {
        // Do implement test here
        testTestApi62->funcInt(0);
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testTestApi62->funcFloat(0.0f);
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testTestApi62->funcString(std::string());
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testTestApi62->setPropInt(0);
        REQUIRE( testTestApi62->getPropInt() == 0 );
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testTestApi62->setPropFloat(0.0f);
        REQUIRE( testTestApi62->getPropFloat() == Approx( 0.0f ) );
    }
    SECTION("Test property propString") {
        // Do implement test here
        testTestApi62->setPropString(std::string());
        REQUIRE( testTestApi62->getPropString() == std::string() );
    }
}
