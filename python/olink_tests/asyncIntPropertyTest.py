import os
import sys
sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), '../test_api')))

from asyncio.events import get_event_loop
import apigear.olink
from api.olink.sinks import TestApi0Sink
from utils.eventhook import EventHook
from olink.client.node import ClientNode
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


class AsyncIntPropertyTest:

    def __init__(self, in_messsages_per_thread, threads):
        self.messsages_per_thread = in_messsages_per_thread
        self.threadsNumber = threads
        total_msgs_nuber = threads*self.messsages_per_thread
        self.counter =  Counter(total_msgs_nuber)
        self.is_test_done = False
        self.node = ClientNode()
        self.client = apigear.olink.Client(self.node)
        self.sink = TestApi0Sink()
        self.is_ready_event = asyncio.Event()
        self.is_server_done = asyncio.Event()
        self.start_times = np.zeros(total_msgs_nuber)
        self.stop_times = np.zeros(total_msgs_nuber)
    
    def on_counter_increased(self, value):
        self.stop_times[value-1] = time.perf_counter_ns()
        self.counter.increase_count()

    def finish_test(self):
        self.is_server_done.set()

    def update_is_ready(self):
        self.is_ready_event.set()

    async def send_and_receive(self):
        await self.is_ready_event.wait()
        thread_tasks = []
        start = time.perf_counter_ns()
        for thread in range(self.threadsNumber):
            thread_tasks.append( Thread(target=self.send_messages, args=(thread, self.messsages_per_thread)))
        for thread in thread_tasks:
            thread.start()
        await self.is_server_done.wait()

        for thread in thread_tasks:
            thread.join()
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
        
        self.node.link_remote(self.sink.olink_object_name())
        self.sink.on_prop_int_changed += self.on_counter_increased
    
        self.sink._on_is_ready+= self.update_is_ready
        self.counter.on_threshold +=  self.finish_test
        
        connectTask =  asyncio.create_task( self.client.connect('ws://localhost:8000/ws'));

        await self.send_and_receive()

        self.node.unlink_remote(self.sink.olink_object_name())
        self.client.disconnect()
        await connectTask

        self.sink.on_prop_int_changed -= self.on_counter_increased
        self.counter.on_threshold -=  self.finish_test
        self.sink._on_is_ready-= self.update_is_ready


    def send_messages(self, thread_no, messages_num):
        for msg_no in range(messages_num):
            number = thread_no*messages_num + msg_no+ +1
            self.start_times[number-1] = time.perf_counter_ns()
            self.sink.set_prop_int(number)


async def main():
    messsages_per_thread = 1
    threads = 1
    args = sys.argv[1:]
    if len(args) > 0:
        messsages_per_thread = int(args[0])
    if len(args) > 1:
        threads = int(args[1])
    test = AsyncIntPropertyTest(messsages_per_thread, threads)
    await test.execute()

if __name__ == '__main__':
    loop = asyncio.new_event_loop()
    asyncio.set_event_loop(loop)
    loop.run_until_complete(main())