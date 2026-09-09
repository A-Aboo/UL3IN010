# Shell Commands and C Functions

# Part 1 — Shell Commands

---

## 1. `man`

### ?

`man` shows the manual/documentation of a command or C function.

### Simple usage

```bash
man ls
```

For a C function:

```bash
man 3 printf
```

### `man -a`

`man -a` shows all manual pages matching the name.

```bash
man -a printf
```

Useful sections:

```text
1 → Shell commands
2 → System calls
3 → C library functions
```

Examples:

```bash
man 1 time
man 2 gettimeofday
man 3 system
```

---

## 2. `time`

### ?

`time` measures how long a command takes to execute.

### Simple example

```bash
time ls
```

Possible output:

```text
real    0m0.010s
user    0m0.002s
sys     0m0.004s
```

Meaning:

```text
real → total elapsed time
user → CPU time in user code
sys  → CPU time in kernel/system code
```

Another example:

```bash
time ./program
```

---

## 3. `nice`

### ?

`nice` starts a program with a different CPU scheduling priority.

Higher nice value means lower priority.

### Simple example

```bash
nice ./program
```

Choose a value:

```bash
nice -n 15 ./program
```

Typical range:

```text
-20 → highest priority
19  → lowest priority
```

---

## 4. `ps`

### ?

`ps` displays information about running processes.

### Simple example

```bash
ps
```

Possible output:

```text
PID    TTY      TIME     CMD
1234   pts/0    00:00    bash
1450   pts/0    00:00    ps
```

Show more processes:

```bash
ps aux
```

Find a specific process:

```bash
ps aux | grep firefox
```

---

# Part 2 — C Functions

---

## 1. `gettimeofday`

### ?

`gettimeofday()` gets the current time since 1 January 1970.

This starting date is called the Unix Epoch.

### Header

```c
#include <sys/time.h>
```

### Simple example

```c
#include <stdio.h>
#include <sys/time.h>

int main(void)
{
    struct timeval time;

    gettimeofday(&time, NULL);

    printf("Seconds: %ld\n", time.tv_sec);
    printf("Microseconds: %ld\n", time.tv_usec);

    return 0;
}
```

Important fields:

```text
tv_sec  → seconds
tv_usec → microseconds
```

---

## 2. `times`

### ?

`times()` gets CPU-time statistics for a process and its child processes.

The values are given in clock ticks.

### Header

```c
#include <sys/times.h>
```

### Simple example

```c
#include <stdio.h>
#include <sys/times.h>

int main(void)
{
    struct tms info;

    times(&info);

    printf("User ticks: %ld\n", info.tms_utime);
    printf("System ticks: %ld\n", info.tms_stime);

    return 0;
}
```

Important fields:

```text
tms_utime  → user CPU time
tms_stime  → system CPU time
tms_cutime → child user CPU time
tms_cstime → child system CPU time
```

---

## 3. `sysconf`

### ?

`sysconf()` gets system configuration information.

For `times()`, we use it to know how many clock ticks exist in one second.

### Header

```c
#include <unistd.h>
```

### Simple example

```c
#include <stdio.h>
#include <unistd.h>

int main(void)
{
    long ticks;

    ticks = sysconf(_SC_CLK_TCK);

    printf("Ticks per second: %ld\n", ticks);

    return 0;
}
```

Possible output:

```text
100
```

Meaning:

```text
100 ticks = 1 second
50 ticks  = 0.5 second
```

---

## 4. `system`

### ?

`system()` executes a shell command from a C program.

### Header

```c
#include <stdlib.h>
```

### Simple example

```c
#include <stdlib.h>

int main(void)
{
    system("ls");

    return 0;
}
```

Another example:

```c
system("pwd");
```

---

# Part 3 — Advanced Shell Examples

---

## Advanced Example 1 — `time`

Measure the execution time of your own program:

```bash
time ./program
```

You may get:

```text
real    0m2.005s
user    0m1.500s
sys     0m0.200s
```

This means:

```text
real → program existed for about 2 seconds
user → program used CPU for 1.5 seconds
sys  → kernel work used 0.2 seconds
```

---

## Advanced Example 2 — `nice`

Suppose you have a CPU-heavy program:

```bash
./heavy_program
```

You can run it with lower priority:

```bash
nice -n 15 ./heavy_program
```

This tells the system:

```text
Other processes can receive CPU time before this program.
```

You can combine it with `time`:

```bash
time nice -n 15 ./heavy_program
```

This:

```text
1. lowers the program priority
2. runs the program
3. measures how long it takes
```

---

## Advanced Example 3 — Compare two `nice` priorities

Run one program normally:

```bash
./program
```

Run another with lower priority:

```bash
nice -n 19 ./program
```

Then inspect them:

```bash
ps -o pid,ni,cmd
```

Possible output:

```text
PID    NI   CMD
2000    0   ./program
2001   19   ./program
```

Here:

```text
NI = nice value
```

So:

```text
0  → normal priority
19 → lower priority
```

---

## Advanced Example 4 — `ps`

Show selected information about running processes:

```bash
ps -eo pid,ppid,ni,%cpu,%mem,cmd
```

Meaning:

```text
PID   → process ID
PPID  → parent process ID
NI    → nice value
%CPU  → CPU usage
%MEM  → memory usage
CMD   → command
```

Example:

```text
PID   PPID   NI   %CPU   %MEM   CMD
1000   900    0    2.1    1.0   firefox
1200  1100   10   85.0    0.5   ./program
```

---

## Advanced Example 5 — Find a process with `ps`

Suppose your program is:

```bash
./my_program
```

Find it:

```bash
ps aux | grep my_program
```

A cleaner method is:

```bash
ps -C my_program
```

Possible output:

```text
PID TTY          TIME CMD
2300 pts/0    00:00:05 my_program
```

---

## Advanced Example 6 — Sort processes by CPU

```bash
ps aux --sort=-%cpu
```

The processes using the most CPU appear first.

You can also show only some columns:

```bash
ps -eo pid,%cpu,%mem,cmd --sort=-%cpu
```

---

## Advanced Example 7 — `nice` + `ps`

Start a program with low priority:

```bash
nice -n 15 ./program
```

Then in another terminal:

```bash
ps -eo pid,ni,%cpu,cmd | grep program
```

Possible result:

```text
5420   15   90.0   ./program
```

Now we can see:

```text
PID  = 5420
NI   = 15
CPU  = 90%
```

So `nice` changes the priority and `ps` lets us inspect it.

---

# Part 4 — Advanced C Examples

---

## Advanced Example 1 — Measure elapsed time with `gettimeofday`

```c
#include <stdio.h>
#include <sys/time.h>

int main(void)
{
    struct timeval start;
    struct timeval end;
    double elapsed;
    long i;

    gettimeofday(&start, NULL);

    i = 0;
    while (i < 100000000)
        i++;

    gettimeofday(&end, NULL);

    elapsed =
        (end.tv_sec - start.tv_sec)
        + (end.tv_usec - start.tv_usec) / 1000000.0;

    printf("Elapsed time: %f seconds\n", elapsed);

    return 0;
}
```

We do:

```text
end - start
```

to get the elapsed time.

---

## Advanced Example 2 — `times` + `sysconf`

`times()` gives ticks, so we convert them to seconds using:

```c
sysconf(_SC_CLK_TCK);
```

Example:

```c
#include <stdio.h>
#include <unistd.h>
#include <sys/times.h>

int main(void)
{
    struct tms info;
    long ticks;
    long i;

    ticks = sysconf(_SC_CLK_TCK);

    i = 0;
    while (i < 100000000)
        i++;

    times(&info);

    printf("User CPU time: %f sec\n",
        (double)info.tms_utime / ticks);

    printf("System CPU time: %f sec\n",
        (double)info.tms_stime / ticks);

    return 0;
}
```

If:

```text
tms_utime = 50
ticks = 100
```

then:

```text
50 / 100 = 0.5 seconds
```

---

## Advanced Example 3 — Compare CPU time before and after

```c
#include <stdio.h>
#include <unistd.h>
#include <sys/times.h>

int main(void)
{
    struct tms before;
    struct tms after;
    long ticks;
    long i;
    double cpu_time;

    ticks = sysconf(_SC_CLK_TCK);

    times(&before);

    i = 0;
    while (i < 100000000)
        i++;

    times(&after);

    cpu_time =
        (double)(after.tms_utime - before.tms_utime)
        / ticks;

    printf("CPU time used: %f sec\n", cpu_time);

    return 0;
}
```

The important calculation is:

```text
after - before
```

---

## Advanced Example 4 — `system`

Execute several shell commands from C:

```c
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    printf("Directory:\n");
    system("pwd");

    printf("\nFiles:\n");
    system("ls -la");

    printf("\nProcesses:\n");
    system("ps");

    return 0;
}
```

This program executes:

```text
pwd
ls -la
ps
```

---

## Advanced Example 5 — Check `system()` result

```c
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int result;

    result = system("ls");

    if (result == -1)
        printf("Could not execute command\n");
    else
        printf("Command executed\n");

    return 0;
}
```

---

## Advanced Example 6 — `gettimeofday` + `system`

Measure how long a shell command takes:

```c
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

int main(void)
{
    struct timeval start;
    struct timeval end;
    double elapsed;

    gettimeofday(&start, NULL);

    system("sleep 2");

    gettimeofday(&end, NULL);

    elapsed =
        (end.tv_sec - start.tv_sec)
        + (end.tv_usec - start.tv_usec) / 1000000.0;

    printf("Command took: %f seconds\n", elapsed);

    return 0;
}
```

Possible output:

```text
Command took: 2.001234 seconds
```

---

# Part 5 — Commands Used Together

Suppose we have:

```bash
./program
```

Measure it:

```bash
time ./program
```

Run it with lower priority:

```bash
nice -n 10 ./program
```

Measure it while changing its priority:

```bash
time nice -n 10 ./program
```

Find the process:

```bash
ps aux | grep program
```

See its priority and CPU usage:

```bash
ps -eo pid,ni,%cpu,%mem,cmd | grep program
```

Read documentation:

```bash
man nice
man ps
man time
```

---

# Quick Summary — Shell

| Command  | Meaning                      |
| -------- | ---------------------------- |
| `man`    | Read documentation           |
| `man -a` | Show all matching manuals    |
| `time`   | Measure execution time       |
| `nice`   | Change starting CPU priority |
| `ps`     | Inspect processes            |

---

# Quick Summary — C

| Function         | Meaning                  |
| ---------------- | ------------------------ |
| `gettimeofday()` | Get current Unix time    |
| `times()`        | Get CPU-time statistics  |
| `sysconf()`      | Get system configuration |
| `system()`       | Run shell command from C |

---

# Easy Way to Remember

```text
man
→ documentation
```

```text
time
→ how long?
```

```text
nice
→ CPU priority
```

```text
ps
→ process information
```

```text
gettimeofday()
→ current / elapsed real time
```

```text
times()
→ CPU time
```

```text
sysconf(_SC_CLK_TCK)
→ ticks per second
```

```text
system()
→ shell command from C
```

---

# Important Difference

```text
gettimeofday()
→ real elapsed time
```

```text
times()
→ CPU usage time
```

Example:

```text
Program exists for 5 seconds.

But CPU is only used for 2 seconds.

gettimeofday → about 5 seconds
times        → about 2 seconds
```

---

# Important Note About `system()`

This is fine:

```c
system("ls");
```

But avoid passing untrusted user input directly to `system()` because the shell interprets special characters.

For more controlled process execution, Unix programs often use:

```text
fork()
exec()
```
