#include <memory>
#include "catch2/catch.hpp"
#include "api/implementation/testapi24.h"

using namespace Cpp::Api;
TEST_CASE("Testing TestApi24", "[TestApi24]"){
    std::unique_ptr<ITestApi24> testTestApi24 = std::make_unique<TestApi24>();
    // setup your test
    SECTION("Test operation funcInt") {
        // Do implement test here
        testTestApi24->funcInt(0);
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testTestApi24->funcFloat(0.0f);
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testTestApi24->funcString(std::string());
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testTestApi24->setPropInt(0);
        REQUIRE( testTestApi24->getPropInt() == 0 );
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testTestApi24->setPropFloat(0.0f);
        REQUIRE( testTestApi24->getPropFloat() == Approx( 0.0f ) );
    }
    SECTION("Test property propString") {
        // Do implement test here
        testTestApi24->setPropString(std::string());
        REQUIRE( testTestApi24->getPropString() == std::string() );
    }
}
