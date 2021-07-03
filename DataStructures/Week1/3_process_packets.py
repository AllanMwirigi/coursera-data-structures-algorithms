# python3

from collections import namedtuple, deque
from queue import Queue

Request = namedtuple("Request", ["arrived_at", "time_to_process"])
Response = namedtuple("Response", ["was_dropped", "started_at"])


class Buffer:
    def __init__(self, size):
        self.size = size
        self.finish_time = []
        self.latest_end_time = 0 # time when the latest packet will end processing
        # self.buffer_q2 = Queue(maxsize=size)
        self.buffer_q = deque(maxlen=size)

    def process(self, request):
        # write your code here
        if self.latest_end_time == 0:
            # the first packet
            self.latest_end_time += request.time_to_process
            self.buffer_q.append({ 'request': request, 'finish_time': self.latest_end_time })
            self.counter += 1
            return Response(False, request.arrived_at)
        else:
            # packets with the same arrival time that don't fit in the buffer will be dropped

            if request.arrived_at >= self.buffer_q[0]['finish_time']:
                self.buffer_q.popleft() # pop off the firstmost packet
            
            if len(self.buffer_q) == self.size: 
                # buffer is full so current packet is dropped
                return Response(True, request.arrived_at) # second parameter not used here
            else:
                start_time = self.latest_end_time # current packet starts processing when last one finishes
                self.latest_end_time += request.time_to_process
                # current packet is buffered
                self.buffer_q.append({ 'request': request, 'finish_time': self.latest_end_time })
                
                self.counter += 1
                return Response(False, start_time)

            # if queue still full, current packet is dropped


def process_requests(requests, buffer):
    responses = []
    for request in requests:
        responses.append(buffer.process(request))
    return responses


def main():
    buffer_size, n_requests = map(int, input().split())
    requests = []
    for _ in range(n_requests):
        arrived_at, time_to_process = map(int, input().split())
        requests.append(Request(arrived_at, time_to_process))

    if len(requests) == 0:
        return

    buffer = Buffer(buffer_size)
    responses = process_requests(requests, buffer)

    for response in responses:
        # print started_at if packet wasn't dropped, otherwise print -1
        print(response.started_at if not response.was_dropped else -1)


if __name__ == "__main__":
    main()
