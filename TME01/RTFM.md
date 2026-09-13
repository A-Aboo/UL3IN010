# C Functions: `atoi`, `rand`, `srand`, `getrusage`

# P 1 —

---

## 1. `atoi`

### ?

`atoi()` converts a string into an integer.

### Header

```c
#include <stdlib.h>
```

### ex

```c
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char *str = "123";
    int n = atoi(str);

    printf("%d\n", n);
    return 0;
}
```

Output:

```text
123
```

For example:

```c
atoi("42");
```

returns:

```text
42
```

### Common usage

It is very useful with command-line arguments:

```c
int n = atoi(argv[1]);
```

Because `argv` contains strings, `atoi()` can convert them to integers.

---

## 2. `rand`

### ?

`rand()` generates a pseudo-random integer.

### Header

```c
#include <stdlib.h>
```

### ex

```c
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int n = rand();

    printf("%d\n", n);
    return 0;
}
```

### Random number from `0` to `9`

```c
int n = rand() % 10;
```

Possible result:

```text
0
1
2
...
9
```

### Random number from `1` to `10`

```c
int n = (rand() % 10) + 1;
```

### General formula

```c
min + rand() % (max - min + 1);
```

Example:

```c
int n = 10 + rand() % 11;
```

This generates a number between:

```text
10 and 20
```

---

## 3. `srand`

### ?

`srand()` initializes the random generator used by `rand()`.

Without `srand()`, `rand()` can generate the same sequence every time the program starts.

### Header

```c
#include <stdlib.h>
```

We usually use it with:

```c
#include <time.h>
```

### ex

```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    srand(time(NULL));

    printf("%d\n", rand() % 100);

    return 0;
}
```

`time(NULL)` changes with time, so the random numbers are different between executions.

### Important

Usually call:

```c
srand(time(NULL));
```

only **once** at the beginning of the program.

Do not do this repeatedly:

```c
srand(time(NULL));
rand();

srand(time(NULL));
rand();
```

Better:

```c
srand(time(NULL));

rand();
rand();
rand();
```

---

## 4. `getrusage`

### ?

`getrusage()` gives information about the resources used by a process.

It can give information about:

* CPU user time
* CPU system time
* memory usage
* context switches

### Header

```c
#include <sys/resource.h>
```

### ex

```c
#include <stdio.h>
#include <sys/resource.h>

int main(void)
{
    struct rusage usage;

    getrusage(RUSAGE_SELF, &usage);

    printf("User CPU time: %ld seconds\n",
        usage.ru_utime.tv_sec);

    return 0;
}
```

Here:

```c
RUSAGE_SELF
```

means:

```text
Get information about the current process.
```

Some useful fields:

```c
usage.ru_utime
```

CPU time used by the program.

```c
usage.ru_stime
```

CPU time used inside the operating system/kernel.

```c
usage.ru_maxrss
```

Maximum memory used by the process.

---

# Part 2 — 

---

## Example 1 — `atoi` with command-line arguments

Suppose we run:

```bash
./program 10 20
```

Program:

```c
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int a;
    int b;

    if (argc != 3)
    {
        printf("Usage: ./program number1 number2\n");
        return 1;
    }

    a = atoi(argv[1]);
    b = atoi(argv[2]);

    printf("Sum = %d\n", a + b);

    return 0;
}
```

Execution:

```bash
./program 10 20
```

Output:

```text
Sum = 30
```

Here:

```c
argv[1]
```

is:

```text
"10"
```

and:

```c
atoi(argv[1])
```

becomes:

```text
10
```

---

## Example 2 — Random number between two values

We can create our own function:

```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int random_range(int min, int max)
{
    return min + rand() % (max - min + 1);
}

int main(void)
{
    srand(time(NULL));

    printf("%d\n", random_range(50, 100));

    return 0;
}
```

Possible output:

```text
73
```

The function:

```c
random_range(50, 100)
```

returns a random number between:

```text
50 and 100
```

---

## Example 3 — Dice simulation

We can simulate a dice using `rand()` and `srand()`.

```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    int i;

    srand(time(NULL));

    i = 0;
    while (i < 5)
    {
        printf("Dice: %d\n", (rand() % 6) + 1);
        i++;
    }

    return 0;
}
```

Possible output:

```text
Dice: 4
Dice: 1
Dice: 6
Dice: 3
Dice: 2
```

Because a dice contains numbers:

```text
1 to 6
```

we use:

```c
(rand() % 6) + 1
```

---

## Example 4 — Measure CPU usage with `getrusage`

We can check CPU usage before and after some work.

```c
#include <stdio.h>
#include <sys/resource.h>

int main(void)
{
    struct rusage before;
    struct rusage after;
    long i;

    getrusage(RUSAGE_SELF, &before);

    i = 0;
    while (i < 100000000)
        i++;

    getrusage(RUSAGE_SELF, &after);

    printf("Before: %ld.%06ld sec\n",
        before.ru_utime.tv_sec,
        before.ru_utime.tv_usec);

    printf("After: %ld.%06ld sec\n",
        after.ru_utime.tv_sec,
        after.ru_utime.tv_usec);

    return 0;
}
```

Here we call:

```c
getrusage()
```

before the loop and after the loop.

Then we can see how much CPU time the program used.

---

# Example 5 — Using `atoi`, `rand`, `srand`, and `getrusage` Together

Suppose the user gives the number of random numbers to generate:

```bash
./program 5
```

Program:

```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/resource.h>

int main(int argc, char **argv)
{
    int count;
    int i;
    struct rusage usage;

    if (argc != 2)
    {
        printf("Usage: ./program count\n");
        return 1;
    }

    count = atoi(argv[1]);

    srand(time(NULL));

    i = 0;
    while (i < count)
    {
        printf("%d\n", (rand() % 100) + 1);
        i++;
    }

    getrusage(RUSAGE_SELF, &usage);

    printf("CPU user time: %ld.%06ld sec\n",
        usage.ru_utime.tv_sec,
        usage.ru_utime.tv_usec);

    return 0;
}
```

Execution:

```bash
./program 5
```

Possible output:

```text
34
72
15
91
46

CPU user time: 0.001234 sec
```

In this example:

```c
atoi()
```

converts:

```c
argv[1]
```

from a string to an integer.

```c
srand()
```

initializes the random generator.

```c
rand()
```

generates the random numbers.

```c
getrusage()
```

gets information about the CPU resources used by the program.

---

# Quick Summary

| Function      | Simple meaning                |
| ------------- | ----------------------------- |
| `atoi()`      | String → Integer              |
| `rand()`      | Generate pseudo-random number |
| `srand()`     | Initialize `rand()`           |
| `getrusage()` | Get process resource usage    |

---

# Easy Way to Remember

```text
atoi
"42" → 42
```

```text
rand
Generate random number
```

```text
srand
Set the starting point for rand
```

```text
getrusage
Check CPU / memory / process usage
```

---

# Important Notes

## `atoi`

```c
atoi("123");
```

returns:

```text
123
```

But `atoi()` does not properly report invalid input errors.

For more serious programs, `strtol()` is usually safer.

---

## `rand`

```c
rand()
```

is **pseudo-random**, not truly random.

It should not be used for security or passwords.

---

## `srand`

Normally use:

```c
srand(time(NULL));
```

once at the beginning.

---

## `getrusage`

Most commonly:

```c
struct rusage usage;

getrusage(RUSAGE_SELF, &usage);
```

Then access information like:

```c
usage.ru_utime
usage.ru_stime
usage.ru_maxrss
```
