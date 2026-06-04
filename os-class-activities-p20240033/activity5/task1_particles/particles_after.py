import threading, time, random, collections

BUFFER_CAPACITY = 100
buffer = collections.deque()
produced = 0
packaged = 0

empty_pairs = threading.Semaphore(50)
full_pairs  = threading.Semaphore(0)
mutex       = threading.Semaphore(1)

running = True

def producer(machine_id):
    global produced
    pair_id = 0
    while running:
        pair_id += 1
        p1 = f"M{machine_id}-{pair_id}-P1"
        p2 = f"M{machine_id}-{pair_id}-P2"
        time.sleep(random.uniform(0.02, 0.08))

        empty_pairs.acquire()
        mutex.acquire()

        if len(buffer) + 2 > BUFFER_CAPACITY:
            print("The producing machine is broken")
            mutex.release()
            return
        buffer.append(p1)
        buffer.append(p2)
        produced += 1

        mutex.release()
        full_pairs.release()

def consumer():
    global packaged
    while running:
        time.sleep(random.uniform(0.03, 0.07))

        full_pairs.acquire()
        mutex.acquire()

        if len(buffer) < 2:
            print("The packaging machine is broken")
            mutex.release()
            return
        p1 = buffer.popleft()
        p2 = buffer.popleft()
        id1 = p1.rsplit("-P", 1)[0]
        id2 = p2.rsplit("-P", 1)[0]
        if id1 != id2:
            print(f"Pairs are incorrect: {p1} + {p2}")
            mutex.release()
            return
        packaged += 1
        buf_size = len(buffer)

        mutex.release()
        empty_pairs.release()

        print(f"Produced pairs: {produced} | Packaged pairs: {packaged} | Buffer particles: {buf_size}")

threads = []
for i in range(1, 4):
    t = threading.Thread(target=producer, args=(i,), daemon=True)
    threads.append(t)
    t.start()

c = threading.Thread(target=consumer, daemon=True)
c.start()

try:
    while True:
        time.sleep(1)
except KeyboardInterrupt:
    print("\nStopped by user (Ctrl+C)")