# Debugging Philosophers (Threads in C)

## 1. Build for Debugging

```bash
tox -e debug-build
# or
make debug
```

This compiles with `-g3 -O0 -DDEBUG` (full symbols, no optimization).

---

## 2. GDB — Basic Thread Debugging

### Start GDB
```bash
gdb --args ./philo 4 410 200 200
```

### Useful GDB Commands

| Command | Description |
|---|---|
| `run` | Start the program |
| `bt` | Backtrace (show call stack) |
| `info threads` | List all threads |
| `thread <N>` | Switch to thread N |
| `thread apply all bt` | Backtrace for ALL threads |
| `break <file>:<line>` | Set breakpoint |
| `break <function>` | Break on function entry |
| `watch <variable>` | Break when variable changes |
| `set scheduler-locking on` | Only run current thread (freeze others) |
| `set scheduler-locking off` | Resume all threads |
| `next` / `step` | Step over / step into |
| `continue` | Resume execution |

### Example Session
```bash
gdb --args ./philo 4 410 200 200
(gdb) break philosopher_routine
(gdb) run
# Hits breakpoint in one thread
(gdb) info threads
# Shows all philosopher threads
(gdb) thread 3
(gdb) bt
# See where thread 3 is
(gdb) set scheduler-locking on
# Now only this thread runs when you step
(gdb) next
(gdb) print shared_data->is_dead
```

---

## 3. Valgrind + Helgrind (Data Race Detection)

```bash
valgrind --tool=helgrind --history-level=full ./philo 4 410 200 200
```

### Or via tox:
```bash
tox -e unit-valgrind    # unit tests under helgrind
tox -e all-valgrind     # everything under helgrind
```

### What Helgrind Detects
- **Data races**: two threads access the same memory without a lock,
  and at least one is a write
- **Lock order violations**: potential deadlocks (lock A then B in one thread,
  B then A in another)
- **Misuse of pthreads API**: destroying a locked mutex, etc.

### Reading Helgrind Output
```
==12345== Possible data race during read of size 4
==12345==    at 0x401234: check_death (monitor.c:42)
==12345==  This conflicts with a previous write of size 4
==12345==    at 0x401567: philosopher_eat (routine.c:28)
```
→ You're reading a variable in `check_death` that's being written in
`philosopher_eat` **without proper mutex protection**.

---

## 4. Thread Sanitizer (TSan)

Faster than helgrind, built into the compiler:

```bash
make fsanitize
./philo 4 410 200 200
# or
tox -e e2e-tsan
```

### TSan output looks like:
```
WARNING: ThreadSanitizer: data race (pid=12345)
  Write of size 4 at 0x... by thread T3:
    #0 set_dead src/monitor.c:15
  Previous read of size 4 at 0x... by thread T1:
    #0 is_dead src/utils.c:42
```

### TSan vs Helgrind

| | TSan | Helgrind |
|---|---|---|
| Speed | ~2-5x slowdown | ~20-100x slowdown |
| Accuracy | Very good | Very thorough |
| Lock-order | No | Yes |
| Setup | Compile flag | Runtime tool |
| Use for | Quick checks | Deep analysis |

**Recommendation**: Use TSan during development, Helgrind before submission.

---

## 5. Common Philosopher Bugs & How to Find Them

### Bug: Data race on `is_dead` flag
**Symptom**: Helgrind/TSan reports race on the death flag.
**Fix**: Protect reads AND writes with the same mutex.

### Bug: Philosopher prints after death
**Symptom**: Messages appear after "died".
**Debug**: Add a check before every `printf` that reads the death flag
under mutex.

### Bug: Deadlock (all philos grab left fork)
**Symptom**: Program hangs, no output.
**Debug**:
```bash
gdb -p $(pidof philo)
(gdb) thread apply all bt
```
All threads will be stuck on `pthread_mutex_lock`.
**Fix**: Even/odd philosophers pick up forks in different order.

### Bug: Philosopher starves (timing issue)
**Symptom**: One philo dies even though timings should work.
**Debug**: Print timestamps of last meal per philosopher.
**Fix**: Check your usleep implementation; `usleep(time_to_eat * 1000)`
may drift. Use a polling loop:
```c
void    precise_sleep(long ms)
{
    long start = get_time_ms();
    while (get_time_ms() - start < ms)
        usleep(100);
}
```

---

## 6. VS Code Debug Configuration

Add to `.vscode/launch.json`:
```json
{
    "version": "0.2.0",
    "configurations": [
        {
            "name": "Debug Philosophers",
            "type": "cppdbg",
            "request": "launch",
            "program": "${workspaceFolder}/philo",
            "args": ["4", "410", "200", "200"],
            "stopAtEntry": false,
            "cwd": "${workspaceFolder}",
            "environment": [],
            "externalConsole": false,
            "MIMode": "gdb",
            "setupCommands": [
                {
                    "description": "Enable pretty-printing",
                    "text": "-enable-pretty-printing"
                },
                {
                    "description": "Follow fork child",
                    "text": "set follow-fork-mode child"
                }
            ],
            "preLaunchTask": "make debug"
        }
    ]
}
```

Add to `.vscode/tasks.json`:
```json
{
    "version": "2.0.0",
    "tasks": [
        {
            "label": "make debug",
            "type": "shell",
            "command": "make debug",
            "group": "build"
        }
    ]
}
```

Then press **F5** to launch the debugger with philosopher arguments.