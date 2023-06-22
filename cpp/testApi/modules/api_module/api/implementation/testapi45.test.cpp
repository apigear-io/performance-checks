#include <memory>
#include "catch2/catch.hpp"
#include "api/implementation/testapi45.h"

using namespace Cpp::Api;
TEST_CASE("Testing TestApi45", "[TestApi45]"){
    std::unique_ptr<ITestApi45> testTestApi45 = std::make_unique<TestApi45>();
    // setup your test
    SECTION("Test operation funcInt") {
        // Do implement test here
        testTestApi45->funcInt(0);
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testTestApi45->funcFloat(0.0f);
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testTestApi45->funcString(std::string());
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testTestApi45->setPropInt(0);
        REQUIRE( testTestApi45->getPropInt() == 0 );
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testTestApi45->setPropFloat(0.0f);
        REQUIRE( testTestApi45->getPropFloat() == Approx( 0.0f ) );
    }
    SECTION("Test property propString") {
        // Do implement test here
        testTestApi45->setPropString(std::string());
        REQUIRE( testTestApi45->getPropString() == std::string() );
    }
}
