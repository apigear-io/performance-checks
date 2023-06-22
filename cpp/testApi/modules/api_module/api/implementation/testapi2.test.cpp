#include <memory>
#include "catch2/catch.hpp"
#include "api/implementation/testapi2.h"

using namespace Cpp::Api;
TEST_CASE("Testing TestApi2", "[TestApi2]"){
    std::unique_ptr<ITestApi2> testTestApi2 = std::make_unique<TestApi2>();
    // setup your test
    SECTION("Test operation funcInt") {
        // Do implement test here
        testTestApi2->funcInt(0);
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testTestApi2->funcFloat(0.0f);
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testTestApi2->funcString(std::string());
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testTestApi2->setPropInt(0);
        REQUIRE( testTestApi2->getPropInt() == 0 );
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testTestApi2->setPropFloat(0.0f);
        REQUIRE( testTestApi2->getPropFloat() == Approx( 0.0f ) );
    }
    SECTION("Test property propString") {
        // Do implement test here
        testTestApi2->setPropString(std::string());
        REQUIRE( testTestApi2->getPropString() == std::string() );
    }
}
