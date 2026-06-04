import threading, time, random, collections

BUFFER_CAPACITY = 100
buffer = collections.deque()
produced = 0
packaged = 0
lock = threading.Lock()
running = True

def producer(machine_id):
    global produced, running
    pair_id = 0
    while running:
        pair_id += 1
        p1 = f"M{machine_id}-{pair_id}-P1"
        p2 = f"M{machine_id}-{pair_id}-P2"
        time.sleep(random.uniform(0.01, 0.05))
        with lock:
            if len(buffer) + 2 > BUFFER_CAPACITY:
                print("The producing machine is broken")
                running = False
                return
            buffer.append(p1)
            buffer.append(p2)
            produced += 1
def consumer():
    global packaged, running
    while running:
        time.sleep(random.uniform(0.001, 0.01))
        with lock:
            if len(buffer) < 2:
                print("The packaging machine is broken")
                running = False
                return
            p1 = buffer.popleft()
            p2 = buffer.popleft()
            id1 = p1.rsplit("-P", 1)[0]
            id2 = p2.rsplit("-P", 1)[0]
            if id1 != id2:
                print(f"Pairs are incorrect: {p1} + {p2}")
                running = False
                return
            packaged += 1
            print(f"Produced: {produced} | Packaged: {packaged} | Buffer: {len(buffer)}")

threads = []
for i in range(1, 4):
    t = threading.Thread(target=producer, args=(i,), daemon=True)
    threads.append(t)
    t.start()
    c = threading.Thread(target=consumer, daemon=True)
c.start()
threads.append(c)

for t in threads:
    t.join(timeout=10)