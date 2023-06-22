#include <memory>
#include "catch2/catch.hpp"
#include "api/implementation/testapi80.h"

using namespace Cpp::Api;
TEST_CASE("Testing TestApi80", "[TestApi80]"){
    std::unique_ptr<ITestApi80> testTestApi80 = std::make_unique<TestApi80>();
    // setup your test
    SECTION("Test operation funcInt") {
        // Do implement test here
        testTestApi80->funcInt(0);
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testTestApi80->funcFloat(0.0f);
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testTestApi80->funcString(std::string());
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testTestApi80->setPropInt(0);
        REQUIRE( testTestApi80->getPropInt() == 0 );
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testTestApi80->setPropFloat(0.0f);
        REQUIRE( testTestApi80->getPropFloat() == Approx( 0.0f ) );
    }
    SECTION("Test property propString") {
        // Do implement test here
        testTestApi80->setPropString(std::string());
        REQUIRE( testTestApi80->getPropString() == std::string() );
    }
}
