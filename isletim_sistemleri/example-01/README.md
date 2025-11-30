# Example 01 – Creating a Child Process using fork()

## Purpose
The primary purpose of this exercise is to understand and demonstrate the creation of a new process (a child process) from an existing process (the parent) using the fundamental **`fork()` system call** in the C programming language under a Unix-like operating system. It also illustrates how the parent and child processes execute concurrently and are differentiated by the return value of `fork()`.

## System Calls / Functions Used
- **`fork()`**: This is the core system call. It creates a new process by duplicating the calling process. It returns:
    - **`0`** to the newly created child process.
    - **`> 0`** (the PID of the child) to the parent process.
    - **`< 0`** if the process creation failed.
- **`getpid()`**: Returns the Process ID (PID) of the calling process.
- **`getppid()`**: Returns the Parent Process ID (PPID) of the calling process.
- **`perror()`**: Prints a system error message.
- **`exit()`**: Terminates the program execution.

## How It Works
1.  The program begins execution in the parent process and prints its initial PID.
2.  The `fork()` system call is invoked, which attempts to duplicate the current process, creating a child process that is an exact copy.
3.  Both processes continue execution immediately after the `fork()` call.
4.  The program uses an `if-else if-else` structure to check the return value of `fork()`:
    * If the return value is **`0`**, the code inside the `else if (pid == 0)` block is executed by the **child process**.
    * If the return value is **greater than `0`** (the child's PID), the code inside the `else` block is executed by the **parent process**.
    * If the return value is **less than `0`**, an error occurred, and the program terminates.

## How to Compile and Run
To compile the C source code and create the executable **`app`** binary:
```bash
$ gcc main.c -o app
