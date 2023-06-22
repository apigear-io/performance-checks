#include <memory>
#include "catch2/catch.hpp"
#include "api/implementation/testapi28.h"

using namespace Cpp::Api;
TEST_CASE("Testing TestApi28", "[TestApi28]"){
    std::unique_ptr<ITestApi28> testTestApi28 = std::make_unique<TestApi28>();
    // setup your test
    SECTION("Test operation funcInt") {
        // Do implement test here
        testTestApi28->funcInt(0);
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testTestApi28->funcFloat(0.0f);
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testTestApi28->funcString(std::string());
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testTestApi28->setPropInt(0);
        REQUIRE( testTestApi28->getPropInt() == 0 );
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testTestApi28->setPropFloat(0.0f);
        REQUIRE( testTestApi28->getPropFloat() == Approx( 0.0f ) );
    }
    SECTION("Test property propString") {
        // Do implement test here
        testTestApi28->setPropString(std::string());
        REQUIRE( testTestApi28->getPropString() == std::string() );
    }
}
