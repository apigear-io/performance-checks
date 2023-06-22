#include <memory>
#include "catch2/catch.hpp"
#include "api/implementation/testapi25.h"

using namespace Cpp::Api;
TEST_CASE("Testing TestApi25", "[TestApi25]"){
    std::unique_ptr<ITestApi25> testTestApi25 = std::make_unique<TestApi25>();
    // setup your test
    SECTION("Test operation funcInt") {
        // Do implement test here
        testTestApi25->funcInt(0);
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testTestApi25->funcFloat(0.0f);
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testTestApi25->funcString(std::string());
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testTestApi25->setPropInt(0);
        REQUIRE( testTestApi25->getPropInt() == 0 );
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testTestApi25->setPropFloat(0.0f);
        REQUIRE( testTestApi25->getPropFloat() == Approx( 0.0f ) );
    }
    SECTION("Test property propString") {
        // Do implement test here
        testTestApi25->setPropString(std::string());
        REQUIRE( testTestApi25->getPropString() == std::string() );
    }
}
