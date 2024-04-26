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
            self.on_threshold.fire()


class SyncSender:
    def __init__(self, msgs_number, startMsgNumber, sendFunction):
        self.threshold = msgs_number
        self.startNumber = startMsgNumber
        self.count = 0
        self.onFinished = asyncio.Event()
        self.on_response_received = EventHook()
        self.on_response_received+= self.send_message
        self.sendFunction = sendFunction
        self.start_times = np.zeros(msgs_number)
        self.stop_times = np.zeros(msgs_number)

    def on_msg_received(self, value):
        #value is +1 than message number
        if value == self.startNumber + self.count + 1:
            self.stop_times[self.count] = time.perf_counter_ns()
            self.count += 1
            if (self.count == self.threshold):
                self.on_response_received-= self.send_message
                self.onFinished.set()
            else:
                self.on_response_received.fire()

    def send_message(self):
        self.start_times[self.count] = time.perf_counter_ns()
        self.sendFunction(self.startNumber + self.count + 1)

    async def start(self):
        self.send_message()
        await self.onFinished.wait()

    def getLatency(self):
        times = (self.stop_times - self.start_times)/1000
        average_latency = (times.sum())/len(times)
        max_latency = times.max()
        min_latency = times.min()
        return average_latency, max_latency, min_latency

class SyncIntPropertyTest:

    def __init__(self, in_messsages_per_thread, threads):
        self.messsages_per_thread = in_messsages_per_thread
        self.threadsNumber = threads
        total_msgs_nuber = self.threadsNumber*self.messsages_per_thread
        self.counter =  Counter(total_msgs_nuber)
        self.is_test_done = False
        self.node = ClientNode()
        self.client = Client(self.node)
        self.sink = TestApi0Sink()
        self.is_ready_event = asyncio.Event()
        self.is_server_done = asyncio.Event()
    
    def on_counter_increased(self, value):
        self.counter.increase_count()

    def finish_test(self):
        self.is_server_done.set()

    def update_is_ready(self):
        self.is_ready_event.set()

    async def send_and_receive(self):
        thread_senders = []
        thread_tasks = []
        for thread in range(self.threadsNumber):
            thread_senders.append(SyncSender(self.messsages_per_thread, thread*self.messsages_per_thread, self.send_message))
            self.sink.on_prop_int_changed+=thread_senders[thread].on_msg_received
        await self.is_ready_event.wait()

        start = time.perf_counter_ns()
        for thread in range(self.threadsNumber):
            thread_tasks.append( asyncio.create_task(thread_senders[thread].start()))
        await self.is_server_done.wait()
        await asyncio.wait(thread_tasks, return_when=asyncio.ALL_COMPLETED)
        end = time.perf_counter_ns()

        average = np.zeros(self.threadsNumber)
        l_max = np.zeros(self.threadsNumber)
        l_min = np.zeros(self.threadsNumber)
        index = 0

        for sender in thread_senders:
            self.sink.on_prop_int_changed-=sender.on_msg_received
            partial_av, partial_max, partial_min = sender.getLatency()
            average[index]= partial_av
            l_max[index] = partial_max
            l_min[index] = partial_min
            index+=1
        print("Time measured [ms]: " + "{:.2f}".format(int((end - start)/1000000)))
        print("Objects number: 1")
        print("Function execution number for each object: "+ str(self.threadsNumber*self.messsages_per_thread))
        print("Latency[us]: mean ", "{:.2f}".format((average.sum())/len(average)), " max ", "{:.2f}".format(l_max.max()), " min ", "{:.2f}".format(l_min.min()))

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


    def send_message(self, msg_value):
        self.sink.set_prop_int(msg_value)


async def main():
    messsages_per_thread = 100
    threads = 1
    args = sys.argv[1:]
    if len(args) > 0:
        messsages_per_thread = int(args[0])
    if len(args) > 1:
        threads = int(args[1])
    test = SyncIntPropertyTest(messsages_per_thread, threads)
    await test.execute()

if __name__ == '__main__':
    loop = asyncio.new_event_loop()
    asyncio.set_event_loop(loop)
    loop.run_until_complete(main())