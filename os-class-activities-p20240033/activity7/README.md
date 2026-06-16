# Class Activity 7 - Reasoning About Deadlock
- **Student Name:** Ouk Puthirith
- **Student ID:** p20240033
- **My personalization:** a = 3 (last digit), b = 3 (second-to-last digit)

---

## Task 1 — Resource Allocation Graphs

### Part A

**Graph 1 — my prediction:**

Cycle? **YES** — P0 → R1 → P1 → R2 → P2 → R0 → P0

Deadlock? **YES** — With single-instance resources, this cycle means every process is waiting for a resource held by another process in the cycle. No process can proceed because each holds one resource and waits for another held by the next process.

![Graph 1](screenshots/task1_graph1.png)

Matched the tool? **YES** — Tool shows deadlock detected.

---

**Graph 2 — my prediction:**

Cycle? **NO** — P2 has no requests, so the chain ends at P2.

Deadlock? **NO** — P2 can finish first (it holds R2 and requests nothing). When P2 finishes, it releases R2, allowing P1 to get R2 and finish. Then P1 releases R1, allowing P0 to get R1 and finish.

![Graph 2](screenshots/task1_graph2.png)

Matched the tool? **YES** — Tool shows no deadlock with finishing order P2 → P1 → P0.

---

### Part B

**(i) Deadlocked 3×3 graph** — edges I used + why it deadlocks:

```
Assignment edges: R0→P0, R1→P1, R2→P2
Request edges:    P0→R1, P1→R2, P2→R0
```

Why it deadlocks: Each process holds one resource and requests the resource held by the next process, creating a perfect circular wait: P0→R1→P1→R2→P2→R0→P0. All three processes are in the cycle, so no one can proceed.

![Built deadlock](screenshots/task1_build_deadlock.png)

---

**(ii) No-cycle graph (≥4 nodes, ≥1 request)** — why it is deadlock-free:

```
Assignment edges: R0→P0, R1→P1, R2→P2
Request edges:    P0→R1, P1→R2
```

Why it is deadlock-free: P2 holds R2 and makes no requests — it can finish immediately. When P2 releases R2, P1 can get it and finish. When P1 releases R1, P0 can get it and finish. The request edges form a chain, not a cycle.

![Built no-cycle](screenshots/task1_build_nocycle.png)

---

## Task 2 — Cycle ≠ Deadlock

**Warm-up (built-in examples)**

1. Why the "Cycle, NO deadlock" example is not deadlocked: Even though a cycle exists, one process in the cycle can finish because there is a spare (free) instance of a resource. The spare instance allows a process to acquire what it needs without waiting for another process to release it. Once that process finishes and releases its resources, the cycle breaks.

2. The single change that causes deadlock: Reducing a resource from 2 instances to 1 instance. When the spare instance disappears, no process can finish because every process now must wait for a resource held by another process. The reduction algorithm gets stuck immediately.

---

**Part A — given scenario**

Available = Total − ΣAlloc:

```
ΣAllocation = [1+0+1, 0+1+0, 0+1+1] = [2, 1, 1]
Available    = [2-2,   1-1,   2-1]   = [0, 0, 1]
```

The cycle (as a path): **P1 → R2 → P2 → R1 → P1**

Process in the cycle that can still finish + why: **P3** is NOT in the cycle — it has Request = [0,0,0] and can finish immediately, releasing its resources to help break the cycle.

| Step | Process | Why Request ≤ Work      | Work after release |
|------|---------|-------------------------|--------------------|
| 1    | P3      | [0,0,0] ≤ [0,0,1] ✓   | [1, 0, 2]          |
| 2    | P2      | [1,0,0] ≤ [1,0,2] ✓   | [1, 1, 3]          |
| 3    | P1      | [0,1,0] ≤ [1,1,3] ✓   | [2, 1, 3]          |

Conclusion: **NOT deadlocked** — finishing order = P3 → P2 → P1

![Given scenario](screenshots/task2_given_nodeadlock.png)

---

After changing P3's request to `0 1 0` — my prediction: This **WILL deadlock** because no process can satisfy Request ≤ Work at the start. P3 was the "savior" process; now P3 also needs R2, which is held by P2, completing the cycle.

Why it deadlocks (reduction terms):

```
Work = [0, 0, 1]
P1 needs [0,1,0] → R2=1 not available ✗
P2 needs [1,0,0] → R1=1 not available ✗
P3 needs [0,1,0] → R2=1 not available ✗
No process can be the first to finish — deadlock.
```

![Given scenario, deadlock](screenshots/task2_given_deadlock.png)

---

**Part B — my own scenario**

Cycle, no deadlock:

```
Resources: R1=2 instances, R2=1 instance

Allocation:          Request:
P0: R1=1, R2=0       P0: R1=0, R2=1
P1: R1=1, R2=0       P1: R1=0, R2=0  ← NO request!
P2: R1=0, R2=1       P2: R1=1, R2=0

Available = [0, 0]
```

Why not deadlocked: P1 has Request = [0,0] and can finish first. When P1 finishes, it releases R1, allowing P2 to get R1 and finish. Then P2 releases R2, allowing P0 to finish.

![Cycle, no deadlock](screenshots/task2_cycle_nodeadlock.png)

My change that caused deadlock: Change P1's Request from [0,0] to [0,1] (P1 now also wants R2).

Why deadlock (reduction terms):

```
Work = [0, 0]
P0 needs [0,1] → R2 not available ✗
P1 needs [0,1] → R2 not available ✗
P2 needs [1,0] → R1 not available ✗
Now ALL processes are in the cycle. No outsider exists to break it.
```

![Deadlock](screenshots/task2_deadlock.png)

---

## Task 3 — Banker's Algorithm (my personalized scenario)

- Max[P0][A] = 7 + (3 mod 3) = 7 + 0 = **7**
- Max[P2][C] = 2 + (3 mod 4) = 2 + 3 = **5**

**Personalized Max Matrix:**

| Proc | A | B | C |
|------|---|---|---|
| P0   | 7 | 5 | 3 |
| P1   | 3 | 2 | 2 |
| P2   | 9 | 0 | 5 |
| P3   | 2 | 2 | 2 |
| P4   | 4 | 3 | 3 |

**Need matrix = Max − Allocation:**

| Proc | A | B | C |
|------|---|---|---|
| P0   | 7 | 4 | 3 |
| P1   | 1 | 2 | 2 |
| P2   | 6 | 0 | 3 |
| P3   | 0 | 1 | 1 |
| P4   | 4 | 3 | 1 |

**Available = Total − ΣAlloc:**

```
ΣAllocation = [0+2+3+2+0, 1+0+0+1+0, 0+0+2+1+2] = [7, 2, 5]
Available    = [10-7, 5-2, 7-5] = [3, 3, 2]
```

**Safety trace (by hand):**

| Step | Process | Why Need ≤ Work         | Work after release      |
|------|---------|-------------------------|-------------------------|
| 1    | P3      | [0,1,1] ≤ [3,3,2] ✓   | [3+2, 3+1, 2+1] = [5, 4, 3] |
| 2    | P1      | [1,2,2] ≤ [5,4,3] ✓   | [5+2, 4+0, 3+0] = [7, 4, 3] |
| 3    | P0      | [7,4,3] ≤ [7,4,3] ✓   | [7+0, 4+1, 3+0] = [7, 5, 3] |
| 4    | P2      | [6,0,3] ≤ [7,5,3] ✓   | [7+3, 5+0, 3+2] = [10, 5, 5] |
| 5    | P4      | [4,3,1] ≤ [10,5,5] ✓  | [10+0, 5+0, 5+2] = [10, 5, 7] |

Conclusion: **SAFE** — safe sequence = P3 → P1 → P0 → P2 → P4

![Safety check](screenshots/task3_safety.png)

Matched the tool? **YES** — Tool found the same safe sequence P3 → P1 → P0 → P2 → P4.

---

**Request I predicted GRANTED:** Process P1 → Request [1, 0, 0]

Checks:
- Request ≤ Need: [1,0,0] ≤ [1,2,2] ✓
- Request ≤ Available: [1,0,0] ≤ [3,3,2] ✓
- Tentative state safety: New Available = [2,3,2], New Need[P1] = [0,2,2]
- Trace: P3 → P1 → P0 → P2 → P4 (all can finish) ✓

Verdict: **GRANTED**

![Grant](screenshots/task3_request_grant.png)

---

**Request I predicted DENIED:** Process P2 → Request [5, 0, 0]

Checks:
- Request ≤ Need: [5,0,0] ≤ [6,0,3] ✓
- Request ≤ Available: [5,0,0] ≤ [3,3,2] ✗ **(5 > 3 — fails)**

Verdict: **DENIED** — Request exceeds available resources (needs 5 of A, only 3 available).

![Deny](screenshots/task3_request_deny.png)

---

## Task 4 — Semaphores and Deadlock

**Case 1 (s1=s2=s3=1) — my answer: NO — cannot deadlock**

Why no cycle can form: P2's acquisition order (s2 → s3) allows it to always finish without waiting for resources held by P1 or P3. P2 finishes, releases s2, and breaks any potential cycle. The most dangerous snapshot has P1 holding s1 waiting for s2, P2 holding s2 waiting for s3, and P3 waiting for s1 — but no cycle exists because P2 can get s3 (free) and finish.

![Case 1](screenshots/task4_case1.png)

Tool confirmed? **YES** — shows no deadlock.

---

**Case 2 (s1=s2=s3=1) — my answer: YES — can deadlock**

Deadlock interleaving:

1. P1: wait(s1) ✓ — holds s1
2. P2: wait(s2) ✓ — holds s2
3. P3: wait(s2) ✗ — blocked on s2
4. P1: wait(s2) ✗ — blocked on s2
5. P2: wait(s3) ✓, print, signal(s3), signal(s2) — releases s2
6. P3: wait(s2) ✓, wait(s3) ✓, wait(s1) ✗ — blocked on s1 held by P1
7. P1: wait(s2) ✗ — blocked on s2 held by P3

Wait-for cycle: **P1 → s2 → P3 → s1 → P1**

![Case 2](screenshots/task4_case2.png)

Tool confirmed? **YES** — shows deadlock with the cycle.

---

**Case 3 (s1=2, s2=1, s3=1) — my answer: NO — cannot deadlock**

What the extra instance of s1 does: With s1=2, two processes can hold s1 simultaneously. In Case 2, P3 was blocked waiting for s1 (held by P1). With two instances, P3 can acquire the second instance of s1 without waiting for P1 to release it. This breaks the circular wait.

Snapshot:

| Proc | Allocation (s1,s2,s3) | Request (s1,s2,s3) |
|------|----------------------|---------------------|
| P1   | 1, 0, 0              | 0, 1, 0             |
| P2   | 0, 0, 0              | 0, 0, 0             |
| P3   | 0, 1, 1              | 1, 0, 0             |

Available = [1, 0, 0], so P3 can get s1 and finish.

![Case 3](screenshots/task4_case3.png)

Tool confirmed? **YES** — shows no deadlock.

---

## Task 5 — Applied Concepts

**1. Four necessary conditions for deadlock — original example: A library book reservation system**

| Condition        | How it applies                                                                                    |
|------------------|---------------------------------------------------------------------------------------------------|
| Mutual Exclusion | Only one student can check out a physical copy of a specific book at a time.                      |
| Hold and Wait    | A student holds reserved books in their cart while waiting for additional books to become available. |
| No Preemption    | The library cannot forcibly take a book back from a student who has checked it out.               |
| Circular Wait    | Student A holds Book X and waits for Book Y; Student B holds Book Y and waits for Book X.        |

Easiest condition to remove: **Hold and Wait** — require students to request all books at once (either reserve all or none). Cost: Lower resource utilization; a student might reserve multiple books, fail to get one, and release all, leaving them empty while others could have used them.

**2. Cycle in single-instance vs multi-instance RAG:**

In a single-instance system, each resource has only one copy, so a cycle means every process must wait indefinitely — no alternative exists. In a multi-instance system, a cycle might include a resource that has a spare instance available; a process in the cycle can acquire that spare instance and finish, breaking the cycle.

**3. Unsafe state vs deadlocked state:**

| Concept          | Definition                                                                                                     |
|------------------|----------------------------------------------------------------------------------------------------------------|
| Unsafe State     | The system cannot guarantee all processes will finish without deadlock, but deadlock hasn't actually happened yet. |
| Deadlocked State | Processes are actually blocked right now, waiting for resources held by each other in a cycle.                 |

Example of unsafe but not deadlocked: Available = [2,0,0], P0 needs [3,0,0] and P1 needs [2,0,0] — the system is unsafe because granting resources could lead to deadlock, but currently no process is blocked.

**4. Deadlock avoidance (Banker's) vs detection + recovery:**

| Aspect       | Banker's Algorithm                                              | Detection + Recovery                                                    |
|--------------|-----------------------------------------------------------------|-------------------------------------------------------------------------|
| Cost         | Requires max needs upfront; restricts resource utilization      | Periodic detection overhead; cost of aborting/rolling back processes    |
| When to choose | Safety-critical systems (medical devices, aircraft control)  | High-performance systems (web servers, databases) where deadlocks are rare |

**5. Why Banker's requires maximum demand in advance:**

The algorithm needs to know each process's worst-case future needs to determine if granting a request now could lead to an unsafe state — it must ensure there exists some sequence where all processes can finish using their maximum stated needs.

Real-world problem: Applications often don't know their maximum resource needs ahead of time (e.g., a web browser doesn't know how many tabs the user will open). This forces either over-estimation (wasting resources) or under-estimation (risking deadlock). Most real systems use detection + recovery instead for this reason.

---

## Reflection

This activity taught me that a cycle is a warning sign, but not always a death sentence — especially in multi-instance systems where spare resources can break the cycle. The key insight is understanding that a cycle is **necessary but not sufficient** for deadlock.

The reduction algorithm (repeatedly finding processes whose requests can be satisfied with available resources) is the real test of whether a system is deadlocked. In multi-instance systems, a process in the cycle that can finish first will break the cycle by releasing its resources.

The Banker's vs Detection trade-off is a classic engineering problem:

- **Banker's** is conservative and safe but requires perfect knowledge of future needs — unrealistic in most real systems.
- **Detection** is pragmatic — it lets problems happen and deals with them, which works well when deadlocks are rare.

In real systems like databases, detection + recovery is more practical because applications rarely know their maximum resource needs, deadlocks are rare, and rollback/abort is well-understood. In mission-critical systems like medical devices, avoidance is preferred because deadlocks would be catastrophic — even if it costs some performance.

The most important takeaway: deadlock prevention is about understanding resource ordering, and the best approach depends on what you're building. There's no single "right" answer — it's always about trade-offs between safety, performance, and complexity.