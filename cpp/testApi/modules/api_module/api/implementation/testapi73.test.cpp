#include <memory>
#include "catch2/catch.hpp"
#include "api/implementation/testapi73.h"

using namespace Cpp::Api;
TEST_CASE("Testing TestApi73", "[TestApi73]"){
    std::unique_ptr<ITestApi73> testTestApi73 = std::make_unique<TestApi73>();
    // setup your test
    SECTION("Test operation funcInt") {
        // Do implement test here
        testTestApi73->funcInt(0);
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testTestApi73->funcFloat(0.0f);
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testTestApi73->funcString(std::string());
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testTestApi73->setPropInt(0);
        REQUIRE( testTestApi73->getPropInt() == 0 );
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testTestApi73->setPropFloat(0.0f);
        REQUIRE( testTestApi73->getPropFloat() == Approx( 0.0f ) );
    }
    SECTION("Test property propString") {
        // Do implement test here
        testTestApi73->setPropString(std::string());
        REQUIRE( testTestApi73->getPropString() == std::string() );
    }
}
