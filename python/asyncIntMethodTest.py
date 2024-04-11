from asyncio.events import get_event_loop
from os import startfile
from test_api.olink_client import Client
from test_api.api_olink.sinks import TestApi0Sink
from test_api.api_api.shared import EventHook
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


class AsyncMethodTest:

    def __init__(self, messsages_per_thread, threads):
        self.messsages_per_thread = messsages_per_thread
        self.threadsNumber = threads
        total_msgs_nuber = threads*messsages_per_thread
        self.counter =  Counter(total_msgs_nuber)
        self.is_test_done = False
        self.node = ClientNode()
        self.client = Client(self.node)
        self.sink = TestApi0Sink()
        self.is_ready_event = asyncio.Event()
        self.is_server_done = asyncio.Event()
        self.start_times = np.zeros(total_msgs_nuber)
        self.stop_times = np.zeros(total_msgs_nuber)
        self.messages_tasks = []
    
    def on_counter_increased(self, value):
        self.counter.increase_count()

    def finish_test(self):
        self.is_server_done.set()

    def update_is_ready(self):
        self.is_ready_event.set()

    async def send_and_receive(self):
        await self.is_ready_event.wait()
        thread_tasks = []
        start = time.time_ns()
        for taskNo in range(self.threadsNumber):
            thread_tasks.append (asyncio.create_task(self.send_messages(taskNo, self.messsages_per_thread)))

        await asyncio.wait(thread_tasks, return_when=asyncio.ALL_COMPLETED)
        await asyncio.wait(self.messages_tasks, return_when=asyncio.ALL_COMPLETED)
        await self.is_server_done.wait()
        end = time.time_ns()

        times = self.stop_times - self.start_times
        avg = (float((times.sum())/len(times)))/1000.0
        l_max = float(times.max())/1000.0
        l_min = float(times.min())/1000.0


        test_time = end-start
        if test_time < 1000:
            print("Time measured [ns]: " + str(test_time))
        elif test_time < 1000000:
            print("Time measured [us]: " + str(int(test_time/1000)))
        else:
            print("Time measured [ms]: " + str(int((end - start)/1000000)))
        print("Objects number: 1")
        print("Function execution number for each object: "+ str(self.threadsNumber*self.messsages_per_thread))
        print("Latency[us]: mean", "{:.2f}".format(avg), " max", "{:.2f}".format(l_max), " min", "{:.2f}".format(l_min))



    async def execute(self):
        self.node.link_remote(self.sink.olink_object_name())
    
        self.sink.on_is_ready+= self.update_is_ready
        self.counter.on_threshold +=  self.finish_test
        
        connectTask =  asyncio.create_task( self.client.connect('ws://localhost:8000/ws'));

        await self.send_and_receive()

        self.node.unlink_remote(self.sink.olink_object_name())
        self.client.disconnect()
        await connectTask
        
        self.counter.on_threshold -=  self.finish_test
        self.sink.on_is_ready-= self.update_is_ready


    async def send_messages(self, thread_no, messages_num):
        for msg_no in range(messages_num):
            number = thread_no*messages_num + msg_no
            self.start_times[number] = time.time_ns()
            self.messages_tasks.append(asyncio.create_task(self.sink.func_int(number)))
            self.messages_tasks[msg_no].add_done_callback(self.method_finished)

    def method_finished(self, future):
        result = future.result()
        self.stop_times[result] = time.time_ns()
        self.counter.increase_count()

async def main():
    messsages_per_thread = 10
    threads = 1
    args = sys.argv[1:]
    if len(args) > 0:
        messsages_per_thread = int(args[0])
    if len(args) > 1:
        threads = int(args[1])
    test = AsyncMethodTest(messsages_per_thread, threads)
    await test.execute()

if __name__ == '__main__':
    loop = asyncio.new_event_loop()
    asyncio.set_event_loop(loop)
    loop.run_until_complete(main())
