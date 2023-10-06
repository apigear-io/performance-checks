#pragma once
#include <string>

// Messages to be send from client(s) to service adapter to inform that it started test or stopped test
namespace TestMessages
{
const std::string clientStartsTestTopic = "StartTestTopic";
const std::string clientStopsTestTopic = "StopTestTopic";
}
