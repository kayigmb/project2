# Project 2

Process Management, System Calls, File I/O, and Multithreading in C

---

## Overview

This project helps you understand basic operating system concepts using simple C programs. It includes:

* Creating processes and communicating between them
* Using `strace` to observe system calls
* Comparing file copy performance
* Using threads and synchronization

---

## Project Files

* `q1.c` → Process creation and pipe
* `q2.c` → File copy using system calls (`read/write`)
* `q2-stdio.c` → File copy using standard I/O (`fread/fwrite`)
* `q3.c` → Multithreaded prime counter
* `q4.c` → Multithreaded file search

Compiled programs:

* `q1`
* `copy-sys`
* `copy_stdio`
* `q3`
* `search`

---

## Compilation Instructions

Use the following commands:

```bash
gcc q1.c -o q1
gcc q2.c -o copy-sys
gcc q2-stdio.c -o copy_stdio
gcc q3.c -o q3 -lpthread -lm
gcc q4.c -o search -lpthread
```

---

## How to Run the Programs

### Question 1: Process Creation and Pipe

```bash
./q1
```

What it does:

* Creates two child processes
* Runs a pipeline similar to: `ps aux | grep root`
* Saves output to a file
* Displays part of the output

Trace system calls:

```bash
strace -f -o trace.txt ./q1
```

---

### Question 2: File Copy Performance

Create a large file:

```bash
dd if=/dev/zero of=bigfile.bin bs=1M count=100
```

Run both versions:

```bash
./copy-sys bigfile.bin out1.bin
./copy_stdio bigfile.bin out2.bin
```

Trace system calls:

```bash
strace -c ./copy-sys bigfile.bin out1.bin
strace -c ./copy_stdio bigfile.bin out2.bin
```

---

### Question 3: Multithreaded Prime Counter

```bash
./q3
```

Expected output:

```
Total primes: 17984
```

---

### Question 4: Multithreaded File Search

```bash
./search keyword output.txt file1.txt file2.txt file3.txt 4
```

Example:

```bash
./search error results.txt log1.txt log2.txt log3.txt 8
```

---

## Performance Explanation

### Question 1

* Uses `fork()` to create processes
* Uses `execvp()` to run commands
* Uses `pipe()` for communication
* `strace` shows how processes interact with the OS

---

### Question 2

* `copy-sys` (read/write): slower, more system calls
* `copy_stdio` (fread/fwrite): faster, fewer system calls
* Buffering in standard I/O improves performance

---

### Question 3

* Work is divided across 16 threads
* Mutex ensures correct shared result
* Final result is accurate

---

### Question 4

* Each thread processes one file
* Mutex protects shared output file
* Best performance occurs near CPU core count
* Too many threads add overhead

---

## Notes

* Run on a Linux environment
* Make sure input files exist before running search
* Use a large file (100MB+) for performance testing

---
