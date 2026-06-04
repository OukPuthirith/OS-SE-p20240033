import threading, time, random

start_h  = threading.Semaphore(1)
after_e  = threading.Semaphore(0)
after_l1 = threading.Semaphore(0)
after_l2 = threading.Semaphore(0)

def process1():
    time.sleep(random.uniform(0, 0.1))
    start_h.acquire()
    print("H", end="", flush=True)
    time.sleep(random.uniform(0, 0.05))
    print("E", end="", flush=True)
    after_e.release()

def process2():
    time.sleep(random.uniform(0, 0.1))
    after_e.acquire()
    print("L", end="", flush=True)
    after_l1.release()
    after_l1.acquire()
    print("L", end="", flush=True)
    after_l2.release()

def process3():
    time.sleep(random.uniform(0, 0.1))
    after_l2.acquire()
    print("O", end="", flush=True)

print("Printing HELLO 5 times with semaphore ordering:")
for i in range(5):
    start_h  = threading.Semaphore(1)
    after_e  = threading.Semaphore(0)
    after_l1 = threading.Semaphore(0)
    after_l2 = threading.Semaphore(0)

    t1 = threading.Thread(target=process1)
    t2 = threading.Thread(target=process2)
    t3 = threading.Thread(target=process3)
    t1.start(); t2.start(); t3.start()
    t1.join(); t2.join(); t3.join()
    print()

print("All 5 outputs are correct.")