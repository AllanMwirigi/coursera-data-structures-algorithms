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
        if request.arrived_at == 0 and self.latest_end_time == 0:
            # the first packet
            self.latest_end_time += request.time_to_process
            self.buffer_q.append({ 'request': request, 'finish_time': self.latest_end_time })
            return Response(False, request.arrived_at)
        else:
            # packets with the same arrival time that don't fit in the buffer will be dropped

            if len(self.buffer_q) > 0 and request.arrived_at >= self.buffer_q[0]['finish_time']:
                # pop off the firstmost packet whenver a packet arrives after the first completes
                self.buffer_q.popleft()
            
            if len(self.buffer_q) == self.size: 
                # buffer is still full so current packet is dropped
                return Response(True, request.arrived_at) # second parameter not used here
            # elif len(self.buffer_q) == 0:
            #     # buffer is empty so current packet is processed immediately
            #     self.latest_end_time = request.time_to_process
            #     return Response(False, request.arrived_at)
            else:
                if request.arrived_at < self.latest_end_time:
                    # if latest_end_time is greater than the current packet's arrive time, then
                    # current packet starts processing when last one finishes
                    # this also applies to packets in buffer with same arrival time
                    start_time = self.latest_end_time 
                    self.latest_end_time += request.time_to_process
                    # current packet is buffered
                    self.buffer_q.append({ 'request': request, 'finish_time': self.latest_end_time })
                    return Response(False, start_time)
                else:
                    # current packet is processed immediately as it arrives later than the previous one processed
                    self.latest_end_time = request.arrived_at + request.time_to_process
                    self.buffer_q.append({ 'request': request, 'finish_time': self.latest_end_time })
                    return Response(False, request.arrived_at)
                    # Input:            Output:         <- Potential scenario
                    # 1 2               
                    # 0 1               0
                    # 2 1               2


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
    out_file = open("3_p.txt", "w")

    for response in responses:
        # print started_at if packet wasn't dropped, otherwise print -1
        print(response.started_at if not response.was_dropped else -1)
        # out_file.write(str(response.started_at) if not response.was_dropped else "-1")
        # out_file.write("\n")


if __name__ == "__main__":
    main()
