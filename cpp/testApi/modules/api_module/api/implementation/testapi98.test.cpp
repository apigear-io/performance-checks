#include <memory>
#include "catch2/catch.hpp"
#include "api/implementation/testapi98.h"

using namespace Cpp::Api;
TEST_CASE("Testing TestApi98", "[TestApi98]"){
    std::unique_ptr<ITestApi98> testTestApi98 = std::make_unique<TestApi98>();
    // setup your test
    SECTION("Test operation funcInt") {
        // Do implement test here
        testTestApi98->funcInt(0);
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testTestApi98->funcFloat(0.0f);
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testTestApi98->funcString(std::string());
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testTestApi98->setPropInt(0);
        REQUIRE( testTestApi98->getPropInt() == 0 );
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testTestApi98->setPropFloat(0.0f);
        REQUIRE( testTestApi98->getPropFloat() == Approx( 0.0f ) );
    }
    SECTION("Test property propString") {
        // Do implement test here
        testTestApi98->setPropString(std::string());
        REQUIRE( testTestApi98->getPropString() == std::string() );
    }
}
