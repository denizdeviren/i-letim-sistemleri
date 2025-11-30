# Example 09 – Creating an Orphan Process

## Purpose
The primary purpose of this exercise is to demonstrate the creation of an **Orphan Process**. An orphan process occurs when a parent process terminates before its child process has finished execution. The operating system handles this by reassigning the orphaned child to the `init` process (PID 1), ensuring the child process can complete and its resources are eventually cleaned up.

## System Calls / Functions Used
- **`fork()`**: Creates the child process.
- **`getpid()`**: Returns the Process ID (PID) of the calling process.
- **`getppid()`**: Returns the Parent Process ID (PPID) of the calling process. This is the crucial call to show the change of parent.
- **`sleep(seconds)`**: Used to pause the child process, ensuring the parent terminates first.
- **`exit(status)`**: Terminates the calling process immediately. The parent uses this to terminate without calling `wait()`.

## How It Works
1.  The parent process calls **`fork()`** to create a child.
2.  The **parent process** prints its PID and the child's PID, then immediately calls **`exit(0)`** without calling `wait()`. The parent terminates while the child is still running.
3.  The **child process** is still running but its original parent is gone. It goes to sleep for 5 seconds.
4.  During this time, the kernel detects the orphaned child and re-parents it to the **`init` process (PID 1)**.
5.  After waking up, the child calls **`getppid()`** again. The returned PPID is now **`1`**, confirming that it has been adopted and is now an orphan process.

## How to Compile and Run
To compile the C source code and create the executable **`app`** binary:
```bash
$ gcc main.c -o app
