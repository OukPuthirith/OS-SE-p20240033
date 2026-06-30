# OS Lab Final Exam — Cover Sheet & Deliverables

## Student Information
* **Student Name:** Ouk Puthirith
* **Student ID:** p20240033
* **Server Username:** se-ouk-puthirith
* **Exam Scenario Value (COMPANY):** OrbitWorks
* **Exam Scenario Value (PRODUCT):** Widget (`buy_widget`)
* **Date & Start Time:** June 30, 2026 / 13:30
* **AI Assistant Used:** Gemini

---

## Part A — Threads, Kernel Mapping & Signals

### Required Screenshots
* **A1 Thread Execution Output:** `![a1_thread_run](partA_threads/images/a1_thread_run.png)`
* **A2 Signal Intercept Output:** `![a2_signal_catch](partA_threads/images/a2_signal_catch.png)`

### Written Question Response
> **Why does a worker thread's joined result reach the main thread, but a forked child's value would not?**

Threads share the same virtual address space, data segments, and heap memory space as their parent process. This architecture allows a worker thread to pass a heap-allocated pointer cleanly back into the main process thread using `pthread_join()`. 

Conversely, when a process calls `fork()`, the kernel creates an isolated, distinct, copy-on-write virtual address space for the child process. Any memory manipulation or value assignment performed inside that child space remains completely hidden from the parent process unless explicit Inter-Process Communication (IPC) mechanisms like pipes, shared memory, or sockets are used.

---

## Part B — Files, Permissions & Special Bits

### Required Screenshots
* **B1 Special Bits & Binary Output:** `![b1_special_bits](partB_security/images/b1_special_bits.png)`

### Written Question Response
> **Translate your private file's final octal mode into the nine-character symbolic string (e.g. 600 → rw-------).**

`rw-------`

---

## Part C — Bash Scripting, PATH & Safe File Scanning

### Required Screenshots
* **C1 Collector Execution Output:** `![c1_collector_run](partC_scripting/images/c1_collector_run.png)`

### Written Question Response
> **Why did greeter fail to run by name before you added your bin directory to PATH?**

The shell interpreter relies strictly on the `$PATH` environment variable—a colon-separated list of directories—to search for binary or executable files when a command is entered by name without a path qualifier. Because the folder containing the `greeter` script wasn't registered in that list initially, the shell failed to map the script name to any valid file location, throwing a "command not found" error.

---

## Part D — Concurrency, a Race Condition & File Locking

### Required Screenshots
* **D2 Patched Swarm Execution Output:** `![d2_patched](partD_secure/images/d2_patched.png)`

### Written Question Response
> **Why did the unpatched swarm sometimes leave more stock than the correct final value (with 80 stock and 50 concurrent buyers)?**

This behavior stems from a classic Time-of-Check-to-Time-of-Use (TOCTOU) race condition. Without advisory locks, multiple background processes execute the read-modify-write critical section simultaneously. 

For example, Process A and Process B might read the `stock.txt` file at the same instant while it reads `80`. Process A calculates `80 - 1 = 79` and saves it. Simultaneously, Process B calculates `80 - 1 = 79` and writes `79` right over it. Two purchases occurred, but the stock only dropped by one. This causes successful purchases to be overwritten and dropped, leaving the final stock counter artificially higher than the correct value of `30`.

---

## Part E — Backups, Archiving & cron Automation

### Required Screenshots
* **E1 Backup Retention Pruning Output:** `![e1_backup_retention](partE_automation/images/e1_backup_retention.png)`

### Written Question Response
> **Archiving vs compression — which one actually shrank the bytes, and why?**

Compression is what actually shrank the bytes. 

* **Archiving (`tar`)** simply collects and bundles multiple independent directory trees and files into a single contiguous output stream file block, retaining its original size data plus structural metadata header bytes.
* **Compression (`gzip`)** parses that stream using mathematical algorithms (DEFLATE / Lempel-Ziv) to replace redundant bit patterns, duplicate strings, and empty spaces with short variable-length tokens, which significantly reduces the physical storage footprint on disk.