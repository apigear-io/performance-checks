#include <memory>
#include "catch2/catch.hpp"
#include "api/implementation/testapi32.h"

using namespace Cpp::Api;
TEST_CASE("Testing TestApi32", "[TestApi32]"){
    std::unique_ptr<ITestApi32> testTestApi32 = std::make_unique<TestApi32>();
    // setup your test
    SECTION("Test operation funcInt") {
        // Do implement test here
        testTestApi32->funcInt(0);
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testTestApi32->funcFloat(0.0f);
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testTestApi32->funcString(std::string());
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testTestApi32->setPropInt(0);
        REQUIRE( testTestApi32->getPropInt() == 0 );
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testTestApi32->setPropFloat(0.0f);
        REQUIRE( testTestApi32->getPropFloat() == Approx( 0.0f ) );
    }
    SECTION("Test property propString") {
        // Do implement test here
        testTestApi32->setPropString(std::string());
        REQUIRE( testTestApi32->getPropString() == std::string() );
    }
}
