# Example 07 – Process Synchronization using wait()

## Purpose
The main purpose of this exercise is to demonstrate the importance of **process synchronization** in a multi-process environment. Specifically, it uses the **`wait()` system call** to ensure that the parent process pauses its execution until its child process has completed, thereby preventing the child from becoming a "zombie" process and ensuring a controlled execution flow.

## System Calls / Functions Used
- **`fork()`**: Creates the child process.
- **`wait()`**: **The key system call.** It suspends the calling (parent) process's execution until one of its children terminates. It also cleans up the child's exit status.
- **`sleep()`**: Used in the child process to simulate a lengthy task, forcing the parent to wait.
- **`WIFEXITED(status)`**: A macro used to check if the child process terminated normally.
- **`WEXITSTATUS(status)`**: A macro used to retrieve the exit status code of the child process.

## How It Works
1.  The parent process calls **`fork()`** to create a child.
2.  The **child process** sleeps for 3 seconds (simulating work) and then terminates with `exit(0)`.
3.  The **parent process** immediately calls **`wait(&status)`**, which causes the parent to block its execution until the child terminates.
4.  Once the child finishes, `wait()` returns, and the parent process is able to retrieve the child's exit status.
5.  This controlled waiting mechanism guarantees that the parent finishes *after* the child's work is complete, which is a fundamental requirement in many operating systems tasks.

## How to Compile and Run
To compile the C source code and create the executable **`app`** binary:
```bash
$ gcc main.c -o app
