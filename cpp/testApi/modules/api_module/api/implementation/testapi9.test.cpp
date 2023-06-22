#include <memory>
#include "catch2/catch.hpp"
#include "api/implementation/testapi9.h"

using namespace Cpp::Api;
TEST_CASE("Testing TestApi9", "[TestApi9]"){
    std::unique_ptr<ITestApi9> testTestApi9 = std::make_unique<TestApi9>();
    // setup your test
    SECTION("Test operation funcInt") {
        // Do implement test here
        testTestApi9->funcInt(0);
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testTestApi9->funcFloat(0.0f);
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testTestApi9->funcString(std::string());
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testTestApi9->setPropInt(0);
        REQUIRE( testTestApi9->getPropInt() == 0 );
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testTestApi9->setPropFloat(0.0f);
        REQUIRE( testTestApi9->getPropFloat() == Approx( 0.0f ) );
    }
    SECTION("Test property propString") {
        // Do implement test here
        testTestApi9->setPropString(std::string());
        REQUIRE( testTestApi9->getPropString() == std::string() );
    }
}
