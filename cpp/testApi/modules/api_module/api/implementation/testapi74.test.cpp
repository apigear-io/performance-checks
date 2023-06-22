#include <memory>
#include "catch2/catch.hpp"
#include "api/implementation/testapi74.h"

using namespace Cpp::Api;
TEST_CASE("Testing TestApi74", "[TestApi74]"){
    std::unique_ptr<ITestApi74> testTestApi74 = std::make_unique<TestApi74>();
    // setup your test
    SECTION("Test operation funcInt") {
        // Do implement test here
        testTestApi74->funcInt(0);
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testTestApi74->funcFloat(0.0f);
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testTestApi74->funcString(std::string());
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testTestApi74->setPropInt(0);
        REQUIRE( testTestApi74->getPropInt() == 0 );
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testTestApi74->setPropFloat(0.0f);
        REQUIRE( testTestApi74->getPropFloat() == Approx( 0.0f ) );
    }
    SECTION("Test property propString") {
        // Do implement test here
        testTestApi74->setPropString(std::string());
        REQUIRE( testTestApi74->getPropString() == std::string() );
    }
}
