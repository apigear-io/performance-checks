#include <memory>
#include "catch2/catch.hpp"
#include "api/implementation/testapi91.h"

using namespace Cpp::Api;
TEST_CASE("Testing TestApi91", "[TestApi91]"){
    std::unique_ptr<ITestApi91> testTestApi91 = std::make_unique<TestApi91>();
    // setup your test
    SECTION("Test operation funcInt") {
        // Do implement test here
        testTestApi91->funcInt(0);
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testTestApi91->funcFloat(0.0f);
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testTestApi91->funcString(std::string());
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testTestApi91->setPropInt(0);
        REQUIRE( testTestApi91->getPropInt() == 0 );
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testTestApi91->setPropFloat(0.0f);
        REQUIRE( testTestApi91->getPropFloat() == Approx( 0.0f ) );
    }
    SECTION("Test property propString") {
        // Do implement test here
        testTestApi91->setPropString(std::string());
        REQUIRE( testTestApi91->getPropString() == std::string() );
    }
}
