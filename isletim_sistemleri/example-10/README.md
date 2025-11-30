# Example 10 – Creating a Zombie Process

## Purpose
The primary purpose of this lab is to demonstrate the creation of a **Zombie Process**. A Zombie Process is a child process that has completed its execution but still has an entry in the process table, as its parent has not yet called **`wait()`** or **`waitpid()`** to retrieve its exit status and release its resources. This exercise highlights the necessity of using the `wait()` family of calls for proper resource management.

## System Calls / Functions Used
- **`fork()`**: Creates the child process.
- **`getpid()`**: Returns the Process ID (PID).
- **`getppid()`**: Returns the Parent Process ID (PPID).
- **`sleep(seconds)`**: Used to delay the parent's termination, giving time to observe the Zombie state using external tools like `ps`.
- **`exit(status)`**: The child uses this to terminate and enter the Zombie state.
- **`wait()`**: **Conspicuously missing.** The absence of this call in the parent process is what causes the child to become a zombie.

## How It Works
1.  The parent process calls **`fork()`** to create a child.
2.  The **child process** immediately calls **`exit(0)`**. The child's resources are freed, but its Process Control Block (PCB) remains in the system with the state **`Z` (zombie)**.
3.  The **parent process** does not call `wait()`. Instead, it sleeps for 10 seconds.
4.  During this 10-second window, the terminated child exists as a **zombie process**. The existence of the zombie can be verified externally by running the command `ps aux | grep Z` in another terminal, where its status will be `<defunct>` or `Z`.
5.  When the parent eventually terminates, the `init` process (PID 1) inherits and automatically cleans up the zombie process.

## How to Compile and Run
To compile the C source code and create the executable **`app`** binary:
```bash
$ gcc main.c -o app
