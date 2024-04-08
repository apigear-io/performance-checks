#from .test_api.olink.core.protocol import Protocol
#from olink.core.types import MsgType, MessageConverter, Name, MessageFormat
from asyncio.events import get_event_loop
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
            print("CURRENT COUNT :")
            print(self.count)
            self.on_threshold.fire()


class ClientTestInt:

    def __init__(self, messsages_per_thread, threads):
        self.messsages_per_thread = messsages_per_thread
        self.threads = threads
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
    
    def on_counter_increased(self, value):
        number = value -1
        self.stop_times[number] = time.time()
        self.counter.increase_count()

    def finish_test(self):
        self.is_server_done.set()

    def update_is_ready(self):
        print("Is Ready")
        self.is_ready_event.set()

    async def send_and_receive(self):
        await self.is_ready_event.wait()
        thread_tasks = []
        start = time.time()
        print("Start test")
        for thread in range(self.threads):
            thread_tasks.append( Thread(target=self.send_messages, args=(thread, self.messsages_per_thread)))
        for thread in thread_tasks:
            thread.start()
        for thread in thread_tasks:
            thread.join()
        await self.is_server_done.wait()
        end = time.time()
        print("Measured time [ms]")
        print((end - start)*1000)


    async def execute(self):
        print("this is test!")
        
        self.node.link_remote(self.sink.olink_object_name())
        self.sink.on_prop_int_changed += self.on_counter_increased
    
        self.sink.on_is_ready+= self.update_is_ready
        self.counter.on_threshold +=  self.finish_test
        
        connectTask =  asyncio.create_task( self.client.connect('ws://localhost:8000/ws'));

        await self.send_and_receive()

        self.node.unlink_remote(self.sink.olink_object_name())
        self.client.disconnect()
        await connectTask

        times = self.stop_times - self.start_times
        print((times.sum()*1000000)/len(times))
        print(times.max()*1000000)
        print(times.min()*1000000)


        self.sink.on_prop_int_changed -= self.on_counter_increased
        self.counter.on_threshold -=  self.finish_test
        self.sink.on_is_ready-= self.update_is_ready


    def send_messages(self, thread_no, messages_num):
        for msg_no in range(messages_num):
            number = thread_no*messages_num + msg_no+ +1
            self.start_times[number-1] = time.time()
            self.sink.set_prop_int(number)


async def main():
    messsages_per_thread = 1000
    threads = 1
    args = sys.argv[1:]
    if len(args) > 0:
        messsages_per_thread = args[0]
    #if len(args) > 1:
    #    threads = args[1]
    test = ClientTestInt(messsages_per_thread, threads)
    await test.execute()

if __name__ == '__main__':
    loop = asyncio.new_event_loop()
    asyncio.set_event_loop(loop)
    loop.run_until_complete(main())