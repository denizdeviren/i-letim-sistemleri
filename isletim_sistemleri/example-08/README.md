# Example 08 – Selective Process Waiting using waitpid()

## Purpose
The primary goal of this exercise is to illustrate the functionality and advantage of the **`waitpid()` system call** over the simpler `wait()`. `waitpid()` provides finer control, allowing a parent process to specifically wait for a **particular child process** to terminate, or to check for termination without blocking the parent's execution (non-blocking).

## System Calls / Functions Used
- **`fork()`**: Used twice to create two independent child processes (`child1` and `child2`).
- **`waitpid(pid, &status, options)`**: **The key system call.**
    - `pid`: Specifies which process to wait for. If greater than 0, it waits for the process with that PID.
    - `&status`: Pointer to store the termination status.
    - `options`: Controls behavior (e.g., `0` for blocking wait, `WNOHANG` for non-blocking).
- **`wait(NULL)`**: Used at the end to clean up any remaining child processes (`child2`) that were not waited for by `waitpid()`.
- **`sleep()`**: Used to simulate different workloads, highlighting that `child2` finishes first but `child1` is waited for.

## How It Works
1.  The parent process creates **two children** (`child1` and `child2`) with different simulated runtimes (`child2` finishes faster).
2.  The parent calls **`waitpid(child1_pid, &status, 0)`**. Despite `child2` potentially finishing first (after 1 second), the parent **blocks** until `child1` (which runs for 3 seconds) terminates.
3.  The return value of `waitpid()` is the PID of the child that terminated and was waited for, confirming that the parent successfully waited only for `child1`.
4.  This selective waiting capability is the main distinction from `wait()`, which waits for *any* child to terminate.

## How to Compile and Run
To compile the C source code and create the executable **`app`** binary:
```bash
$ gcc main.c -o app
