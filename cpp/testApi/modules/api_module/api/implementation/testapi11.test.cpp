#include <memory>
#include "catch2/catch.hpp"
#include "api/implementation/testapi11.h"

using namespace Cpp::Api;
TEST_CASE("Testing TestApi11", "[TestApi11]"){
    std::unique_ptr<ITestApi11> testTestApi11 = std::make_unique<TestApi11>();
    // setup your test
    SECTION("Test operation funcInt") {
        // Do implement test here
        testTestApi11->funcInt(0);
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testTestApi11->funcFloat(0.0f);
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testTestApi11->funcString(std::string());
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testTestApi11->setPropInt(0);
        REQUIRE( testTestApi11->getPropInt() == 0 );
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testTestApi11->setPropFloat(0.0f);
        REQUIRE( testTestApi11->getPropFloat() == Approx( 0.0f ) );
    }
    SECTION("Test property propString") {
        // Do implement test here
        testTestApi11->setPropString(std::string());
        REQUIRE( testTestApi11->getPropString() == std::string() );
    }
}
