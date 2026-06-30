# live_mods.md — Live Modification (curveball) answers

> Released once, late in the exam. **Three curveballs: A, D, E.** For EACH, give: the
> announced instruction, the exact command(s) you ran, the **live value(s)** you acted
> on (your PID / stock / timestamp), and the screenshot. An answer that ignores your
> issued value, or that could have been written *before* the announcement, scores zero.

---

## Curveball A — extra worker(s) that start after the others join

- **Issued value:** 2 extra workers
- **Announced instruction:** Modify thread_demo.c to spawn 2 extra worker threads only after the primary 3 worker threads have finished execution and successfully joined back to the main thread.
- **Live value(s) I acted on:** base PID = `24105`; new LWP id(s) that appeared = `24109, 24110`
- **Commands:**

```bash
cd ~/OS-SE-p20240033/final-exam/partA_threads
nano thread_demo.c
gcc -pthread thread_demo.c -o thread_demo
./thread_demo & ps -eLf | grep thread_demo > thread_map.txt
```

- **Screenshot:**

![A live — new LWP appears then is gone](partA_threads/images/live_a.png)

---

## Curveball D — per-buyer purchase cap

- **Issued value:** cap = `<N>`
- **Announced instruction:** <paste>
- **Live value(s) I acted on:** stock before = `<...>`; order(s) rejected for exceeding
  the cap = `<...>`; final stock = `<...>`
- **Commands:**

```bash
# add a per-buyer cap to buy_<product>: reject any single order above <N>
# reset stock, re-run swarm, show it stays consistent AND respects the cap
<your commands>
cd ~/OS-SE-p20240033/final-exam/partD_secure/scripts
nano buy_widget
./init_stock
./swarm
./buy_widget "Cap_Tester" 6
cat ../stock.txt
```

- **Screenshot:**

![D live — locked result respects the cap](partD_secure/images/live_d.png)

---

## Curveball E — idempotent timed_job

- **Issued value:** token = `<TOKEN>`
- **Announced instruction:** <paste>
- **Live value(s) I acted on:** today's marker line = `<...>`; 1st trigger = ran,
  2nd trigger = skipped
- **Commands:**

```bash
# add a guard to timed_job: refuse to run if today's <TOKEN> entry is already in the log
# trigger it twice and show the 2nd run was skipped
<your commands>
cd ~/OS-SE-p20240033/final-exam/partE_automation/scripts
nano timed_job
./timed_job >> ../logs/cron_recurring.log
./timed_job >> ../logs/cron_recurring.log
cat ../logs/cron_recurring.log
```

- **Screenshot:**

![E live — 2nd run skipped](partE_automation/images/live_e.png)
