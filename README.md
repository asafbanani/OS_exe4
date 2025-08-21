# OS Assignment -- Interprocess Communication with fork, exec, and pipes

**Overview:**\
This project is part of an Operating Systems course. The task was to
rewrite the program **nicecmp** so that it no longer implements
comparison functions itself, but instead delegates the comparison work
to the external program **loopcmp**.

The rewritten program uses **fork**, **exec**, **dup2**, and **pipe**
system calls to communicate between parent and child processes. Each
child process runs `loopcmp` with a specific comparison mode (`lexcmp`
or `lencmp`), while the parent (`nicecmp`) collects input from the user,
sends it to the appropriate child via a pipe, and reads back the result
through another pipe.

This design demonstrates interprocess communication (IPC) and separation
of responsibilities between parent and child processes.

------------------------------------------------------------------------

**Environment & Compilation:**\
- **Operating System:** Linux\
- **Implementation:** Written in C, using POSIX system calls (`fork`,
`exec`, `pipe`, `dup2`, `waitpid`).\
- **Compilation:** Managed with a custom Makefile.

``` bash
make
```

------------------------------------------------------------------------

**Execution:**\
Run the program once from the terminal:

``` bash
./nicecmp
```

The program repeatedly:\
1. Prompts the user for two strings.\
2. Asks the user to choose a comparison method (lexicographic or
length).\
3. Sends the strings to the appropriate child process.\
4. Receives and prints the result.

------------------------------------------------------------------------

**Key Difference from Assignment 3:**\
While assignment 3 focused on launching comparison programs dynamically,
assignment 4 emphasizes **persistent interprocess communication**: the
children (`loopcmp`) stay alive and serve multiple requests, and
`nicecmp` acts as a manager, orchestrating the flow of data through
pipes.
