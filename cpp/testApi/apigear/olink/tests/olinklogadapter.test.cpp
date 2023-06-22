#pragma warning (disable: 4251) 
#pragma warning (disable: 4099) 

#include <catch2/catch.hpp>
#include "../olinklogadapter.h"

namespace tests{

SCENARIO("Test olink log mapLevel", "[olink][log]")
{
    WHEN("ObjectLink Debug") {
        THEN("Utilities Debug") {
            REQUIRE(ApiGear::Utilities::mapLogLevel(ApiGear::ObjectLink::LogLevel::Debug) == ApiGear::Utilities::LogLevel::Debug);
        }
    }

    WHEN("ObjectLink Info") {
        THEN("Utilities Info") {
            REQUIRE(ApiGear::Utilities::mapLogLevel(ApiGear::ObjectLink::LogLevel::Info) == ApiGear::Utilities::LogLevel::Info);
        }
    }

    WHEN("ObjectLink Warning") {
        THEN("Utilities Warning") {
            REQUIRE(ApiGear::Utilities::mapLogLevel(ApiGear::ObjectLink::LogLevel::Warning) == ApiGear::Utilities::LogLevel::Warning);
        }
    }
    
    WHEN("ObjectLink Error") {
        THEN("Utilities Error") {
            REQUIRE(ApiGear::Utilities::mapLogLevel(ApiGear::ObjectLink::LogLevel::Error) == ApiGear::Utilities::LogLevel::Error);
        }
    }
    
    WHEN("ObjectLink Undefined") {
        THEN("Utilities Debug") {
            REQUIRE(ApiGear::Utilities::mapLogLevel(static_cast<ApiGear::ObjectLink::LogLevel>(10)) == ApiGear::Utilities::LogLevel::Debug);
        }
    }
}

}// namespace tests