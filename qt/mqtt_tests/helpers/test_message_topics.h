#pragma once

// Messages to be send from client(s) to service adapter to inform that it started test or stopped test
namespace TestMessages
{
const QString clientStartsTestTopic = "StartTestTopic";
const QString clientStopsTestTopic = "StopTestTopic";
}
