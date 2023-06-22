#include <memory>
#include "catch2/catch.hpp"
#include "api/implementation/testapi46.h"

using namespace Cpp::Api;
TEST_CASE("Testing TestApi46", "[TestApi46]"){
    std::unique_ptr<ITestApi46> testTestApi46 = std::make_unique<TestApi46>();
    // setup your test
    SECTION("Test operation funcInt") {
        // Do implement test here
        testTestApi46->funcInt(0);
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testTestApi46->funcFloat(0.0f);
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testTestApi46->funcString(std::string());
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testTestApi46->setPropInt(0);
        REQUIRE( testTestApi46->getPropInt() == 0 );
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testTestApi46->setPropFloat(0.0f);
        REQUIRE( testTestApi46->getPropFloat() == Approx( 0.0f ) );
    }
    SECTION("Test property propString") {
        // Do implement test here
        testTestApi46->setPropString(std::string());
        REQUIRE( testTestApi46->getPropString() == std::string() );
    }
}
