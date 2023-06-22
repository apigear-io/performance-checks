/**
Tracer Test
Copyright (C) 2020 ApiGear UG
*/
#include "catch2/catch.hpp"
#include "tracer.h"

using namespace ApiGear::PocoImpl;

TEST_CASE("Testing Tracer", "[Tracer]"){
    Tracer testTracer;
    testTracer.connect("http://localhost:5555", "unitTest");
    std::string modulename = "tracer.test.org";
    std::string interfacename = "tester";

    // setup your test
    SECTION("Test operation call") {
        std::string symbol = modulename + "." + interfacename+"#testCall";
        nlohmann::json fields;

        nlohmann::json obj;
        obj["Age"] = 5;
        obj["Profession"] = "Programmer";
        fields["Annabelle"] = obj;

        testTracer.call(symbol, fields);
    }

    SECTION("Test operation signal") {
        // Do implement test here
    }

    SECTION("Test operation state") {
        std::string symbol = modulename + "." + interfacename+"#_state";
        nlohmann::json fields;

        fields["Age"] = 5;
        fields["Profession"] = "Programmer";

        testTracer.state(symbol, fields);
    }

    Poco::Thread::sleep(500);
}
