#include <memory>
#include "catch2/catch.hpp"
#include "api/implementation/testapi94.h"

using namespace Cpp::Api;
TEST_CASE("Testing TestApi94", "[TestApi94]"){
    std::unique_ptr<ITestApi94> testTestApi94 = std::make_unique<TestApi94>();
    // setup your test
    SECTION("Test operation funcInt") {
        // Do implement test here
        testTestApi94->funcInt(0);
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testTestApi94->funcFloat(0.0f);
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testTestApi94->funcString(std::string());
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testTestApi94->setPropInt(0);
        REQUIRE( testTestApi94->getPropInt() == 0 );
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testTestApi94->setPropFloat(0.0f);
        REQUIRE( testTestApi94->getPropFloat() == Approx( 0.0f ) );
    }
    SECTION("Test property propString") {
        // Do implement test here
        testTestApi94->setPropString(std::string());
        REQUIRE( testTestApi94->getPropString() == std::string() );
    }
}
