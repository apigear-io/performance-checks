#include <memory>
#include "catch2/catch.hpp"
#include "api/implementation/testapi68.h"

using namespace Cpp::Api;
TEST_CASE("Testing TestApi68", "[TestApi68]"){
    std::unique_ptr<ITestApi68> testTestApi68 = std::make_unique<TestApi68>();
    // setup your test
    SECTION("Test operation funcInt") {
        // Do implement test here
        testTestApi68->funcInt(0);
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testTestApi68->funcFloat(0.0f);
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testTestApi68->funcString(std::string());
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testTestApi68->setPropInt(0);
        REQUIRE( testTestApi68->getPropInt() == 0 );
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testTestApi68->setPropFloat(0.0f);
        REQUIRE( testTestApi68->getPropFloat() == Approx( 0.0f ) );
    }
    SECTION("Test property propString") {
        // Do implement test here
        testTestApi68->setPropString(std::string());
        REQUIRE( testTestApi68->getPropString() == std::string() );
    }
}
