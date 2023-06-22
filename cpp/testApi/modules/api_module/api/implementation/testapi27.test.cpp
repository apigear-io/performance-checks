#include <memory>
#include "catch2/catch.hpp"
#include "api/implementation/testapi27.h"

using namespace Cpp::Api;
TEST_CASE("Testing TestApi27", "[TestApi27]"){
    std::unique_ptr<ITestApi27> testTestApi27 = std::make_unique<TestApi27>();
    // setup your test
    SECTION("Test operation funcInt") {
        // Do implement test here
        testTestApi27->funcInt(0);
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testTestApi27->funcFloat(0.0f);
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testTestApi27->funcString(std::string());
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testTestApi27->setPropInt(0);
        REQUIRE( testTestApi27->getPropInt() == 0 );
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testTestApi27->setPropFloat(0.0f);
        REQUIRE( testTestApi27->getPropFloat() == Approx( 0.0f ) );
    }
    SECTION("Test property propString") {
        // Do implement test here
        testTestApi27->setPropString(std::string());
        REQUIRE( testTestApi27->getPropString() == std::string() );
    }
}
