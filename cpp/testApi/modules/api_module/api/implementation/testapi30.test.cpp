#include <memory>
#include "catch2/catch.hpp"
#include "api/implementation/testapi30.h"

using namespace Cpp::Api;
TEST_CASE("Testing TestApi30", "[TestApi30]"){
    std::unique_ptr<ITestApi30> testTestApi30 = std::make_unique<TestApi30>();
    // setup your test
    SECTION("Test operation funcInt") {
        // Do implement test here
        testTestApi30->funcInt(0);
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testTestApi30->funcFloat(0.0f);
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testTestApi30->funcString(std::string());
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testTestApi30->setPropInt(0);
        REQUIRE( testTestApi30->getPropInt() == 0 );
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testTestApi30->setPropFloat(0.0f);
        REQUIRE( testTestApi30->getPropFloat() == Approx( 0.0f ) );
    }
    SECTION("Test property propString") {
        // Do implement test here
        testTestApi30->setPropString(std::string());
        REQUIRE( testTestApi30->getPropString() == std::string() );
    }
}
