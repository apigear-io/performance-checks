#include <memory>
#include "catch2/catch.hpp"
#include "api/implementation/testapi59.h"

using namespace Cpp::Api;
TEST_CASE("Testing TestApi59", "[TestApi59]"){
    std::unique_ptr<ITestApi59> testTestApi59 = std::make_unique<TestApi59>();
    // setup your test
    SECTION("Test operation funcInt") {
        // Do implement test here
        testTestApi59->funcInt(0);
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testTestApi59->funcFloat(0.0f);
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testTestApi59->funcString(std::string());
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testTestApi59->setPropInt(0);
        REQUIRE( testTestApi59->getPropInt() == 0 );
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testTestApi59->setPropFloat(0.0f);
        REQUIRE( testTestApi59->getPropFloat() == Approx( 0.0f ) );
    }
    SECTION("Test property propString") {
        // Do implement test here
        testTestApi59->setPropString(std::string());
        REQUIRE( testTestApi59->getPropString() == std::string() );
    }
}
