#include <memory>
#include "catch2/catch.hpp"
#include "api/implementation/testapi87.h"

using namespace Cpp::Api;
TEST_CASE("Testing TestApi87", "[TestApi87]"){
    std::unique_ptr<ITestApi87> testTestApi87 = std::make_unique<TestApi87>();
    // setup your test
    SECTION("Test operation funcInt") {
        // Do implement test here
        testTestApi87->funcInt(0);
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testTestApi87->funcFloat(0.0f);
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testTestApi87->funcString(std::string());
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testTestApi87->setPropInt(0);
        REQUIRE( testTestApi87->getPropInt() == 0 );
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testTestApi87->setPropFloat(0.0f);
        REQUIRE( testTestApi87->getPropFloat() == Approx( 0.0f ) );
    }
    SECTION("Test property propString") {
        // Do implement test here
        testTestApi87->setPropString(std::string());
        REQUIRE( testTestApi87->getPropString() == std::string() );
    }
}
