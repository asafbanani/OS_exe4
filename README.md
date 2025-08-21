# OS Assignment – Interprocess Communication with Pipes and fork/exec

## Overview
This project is part of an Operating Systems course.  
The task was to implement a program (`nicecmp`) that manages string comparison tasks using child processes and interprocess communication (IPC).  

Two comparison methods are supported:
- **Lexicographic comparison** (`lexcmp`)
- **Length comparison** (`lencmp`)

The main program creates child processes on demand (via `fork` and `exec`) and communicates with them through **pipes**.

---

## Environment & Compilation
- **Operating System:** Linux  
- **Implementation:** Written in C, using POSIX system calls (`fork`, `exec`, `pipe`, `dup2`, `waitpid`)  
- **Compilation:** Managed with a custom Makefile

```bash
make
```

---

## Execution
Run the program once from the terminal:

```bash
./nicecmp
```

The program repeatedly:
1. Prompts the user for two strings.  
2. Asks the user to choose a comparison method (lexicographic or length).  
3. Sends the strings to the appropriate child process.  
4. Receives and prints the result.  

---

## Key Difference from Assignment 3
While assignment 3 focused on launching comparison programs dynamically,  
assignment 4 emphasizes **persistent interprocess communication**: once the child processes are created, they remain alive and are reused for multiple comparisons.

---

## Example Session
```
Please enter first string:
ada
Please enter second string:
adaro
Please choose:
0 - lexcmp
1 - lencmp
1
lencmp(ada, adaro) == -2
```

---

## Cleaning Up
To remove compiled executables:

```bash
make clean
```
