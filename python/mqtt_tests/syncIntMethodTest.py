import os
import sys
sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), '../test_api')))

from asyncio.events import get_event_loop
import apigear.mqtt
from api.mqtt.sinks import TestApi0ClientAdapter
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


class SyncIntMethodTest:

    def __init__(self, messsages_per_thread, threads):
        self.messsages_per_thread = messsages_per_thread
        self.threadsNumber = threads
        total_msgs_nuber = threads*messsages_per_thread
        self.counter =  Counter(total_msgs_nuber)
        self.is_test_done = False
        self.client = apigear.mqtt.Client("uniqueClientIdTestIntProperty")
        self.sink = TestApi0ClientAdapter(self.client)
        self.is_server_done = asyncio.Event()
        self.start_times = np.zeros(total_msgs_nuber)
        self.stop_times = np.zeros(total_msgs_nuber)
    
    def on_counter_increased(self, value):
        self.counter.increase_count()

    def finish_test(self):
        def func():
            self.client.disconnect()
            self.is_server_done.set()
        self.loop.call_soon_threadsafe(func)

    async def send_and_receive(self):
        thread_tasks = []
        start = time.perf_counter_ns()
        for taskNo in range(self.threadsNumber):
            thread_tasks.append (asyncio.create_task(self.send_messages(taskNo, self.messsages_per_thread)))

        await asyncio.wait(thread_tasks, return_when=asyncio.ALL_COMPLETED)
        await self.is_server_done.wait()
        end = time.perf_counter_ns()

        times = self.stop_times - self.start_times
        avg = (times.sum()/1000)/len(times)
        l_max = times.max()/1000
        l_min = times.min()/1000

        print("Time measured [ms]: " + "{:.2f}".format(int((end - start)/1000000)))
        print("Objects number: 1")
        print("Function execution number for each object: "+ str(self.threadsNumber*self.messsages_per_thread))
        print("Latency[us]: mean ", "{:.2f}".format(avg), " max ", "{:.2f}".format(l_max), " min ", "{:.2f}".format(l_min))



    async def execute(self):
        self.loop = asyncio.get_event_loop()
        self.counter.on_threshold +=  self.finish_test
        
        await self.client.connect("localhost", 1883)
        self.client.set_remote_property("StartTestTopic", "someName");
        
        await self.send_and_receive()
        
        self.client.set_remote_property("StopTestTopic", "someName");
        time.sleep(1)
        self.client.disconnect()
        
        self.counter.on_threshold -=  self.finish_test


    async def send_messages(self, thread_no, messages_num):
        for msg_no in range(messages_num):
            number = thread_no*messages_num + msg_no
            self.start_times[number] = time.perf_counter_ns()
            execution = self.sink.func_int(number)
            result = await execution
            if result != number:
                print ("wrong data send")
                print(number)
                print ("received")
                print(result)
            self.stop_times[result] = time.perf_counter_ns()
            self.counter.increase_count()



async def main():
    messsages_per_thread = 10
    threads = 1
    args = sys.argv[1:]
    if len(args) > 0:
        messsages_per_thread = int(args[0])
    if len(args) > 1:
        threads = int(args[1])
    test = SyncIntMethodTest(messsages_per_thread, threads)
    await test.execute()

if __name__ == '__main__':
    loop = asyncio.new_event_loop()
    asyncio.set_event_loop(loop)
    loop.run_until_complete(main())