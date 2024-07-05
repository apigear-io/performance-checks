import os
import sys
sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), '../test_api')))


from asyncio.events import get_event_loop
import apigear.mqtt
from api.mqtt.sources import TestApi0ServiceAdapter
import api.impl
from utils.eventhook import EventHook
import asyncio
import sys
import websockets
import numpy as np
from threading import Thread
import time

class Counter:
    def __init__(self, in_threshold):
        self.threshold = in_threshold
        self.count = 0
        self.on_threshold = EventHook()

    def increase_count(self):
        self.count += 1
        if (self.count == self.threshold):
            self.on_threshold.fire()



class ServerRunning:

    def __init__(self):
        self.service = apigear.mqtt.Service("uniqueServiceIdTestIntProperty")
        self.source = api.impl.TestApi0()
        self.serviceAdapter = TestApi0ServiceAdapter(self.source, self.service)
        self.is_server_done = asyncio.Event()
    
    def finish_test(self):
        def func():
            self.client.disconnect()
            self.is_server_done.set()
        self.loop.call_soon_threadsafe(func)     

    async def execute(self):
        self.loop = asyncio.get_event_loop()   
        await self.service.connect("localhost", 1883)
        #self.service.client.subscribe("StartTestTopic", startCallback);
        self.service._subscribe("StopTestTopic", self.finish_test);
        await self.is_server_done.wait()
        self.service.disconnect()

async def main():
    test = ServerRunning()
    await test.execute()

if __name__ == '__main__':
    loop = asyncio.new_event_loop()
    asyncio.set_event_loop(loop)
    loop.run_until_complete(main())