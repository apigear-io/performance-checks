#include <memory>
#include "catch2/catch.hpp"
#include "api/implementation/testapi88.h"

using namespace Cpp::Api;
TEST_CASE("Testing TestApi88", "[TestApi88]"){
    std::unique_ptr<ITestApi88> testTestApi88 = std::make_unique<TestApi88>();
    // setup your test
    SECTION("Test operation funcInt") {
        // Do implement test here
        testTestApi88->funcInt(0);
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testTestApi88->funcFloat(0.0f);
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testTestApi88->funcString(std::string());
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testTestApi88->setPropInt(0);
        REQUIRE( testTestApi88->getPropInt() == 0 );
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testTestApi88->setPropFloat(0.0f);
        REQUIRE( testTestApi88->getPropFloat() == Approx( 0.0f ) );
    }
    SECTION("Test property propString") {
        // Do implement test here
        testTestApi88->setPropString(std::string());
        REQUIRE( testTestApi88->getPropString() == std::string() );
    }
}
