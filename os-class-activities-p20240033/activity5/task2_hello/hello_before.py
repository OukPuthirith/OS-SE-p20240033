import threading, time, random

def process1():
    time.sleep(random.uniform(0, 0.1))
    print("H", end="", flush=True)
    time.sleep(random.uniform(0, 0.1))
    print("E", end="", flush=True)

def process2():
    time.sleep(random.uniform(0, 0.1))
    print("L", end="", flush=True)
    time.sleep(random.uniform(0, 0.1))
    print("L", end="", flush=True)

def process3():
    time.sleep(random.uniform(0, 0.1))
    print("O", end="", flush=True)

print("Running 5 times to show unpredictable ordering:")
for i in range(5):
    t1 = threading.Thread(target=process1)
    t2 = threading.Thread(target=process2)
    t3 = threading.Thread(target=process3)
    t1.start(); t2.start(); t3.start()
    t1.join(); t2.join(); t3.join()
    print()

print("Output is non-deterministic — letters can appear in wrong order.")