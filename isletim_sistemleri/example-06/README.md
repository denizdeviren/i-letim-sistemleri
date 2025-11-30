# Example 06 – Duplicating File Descriptors using dup()

## Purpose
The primary purpose of this lab is to demonstrate the functionality of the **`dup()` system call**. `dup()` creates a duplicate of an existing file descriptor, allowing two different file descriptors to point to the same open file description. This means they share the same file access mode, same file offset (read/write pointer), and same status flags.

## System Calls / Functions Used
- **`dup(oldfd)`**: The core system call. It creates a copy of the file descriptor `oldfd` using the lowest-numbered available file descriptor.
- **`open()`**: Opens the file and returns the initial file descriptor (`fd1`).
- **`write()`**: Used to write data to the file using both the original (`fd1`) and the duplicated (`fd2`) descriptors.
- **`close()`**: Used to close both file descriptors. Since the file description is shared, the file is only fully closed when the *last* descriptor referring to it is closed.

## How It Works
1.  A file (`dup_test.txt`) is opened, and its descriptor (`fd1`) is obtained.
2.  **`dup(fd1)`** is called, which returns a new descriptor (`fd2`) that is a copy of `fd1`. Both now point to the same open file.
3.  When data is written using `fd1`, the file pointer advances.
4.  When data is subsequently written using `fd2`, the data starts precisely where the file pointer was left by `fd1`. This proves that the offset is shared between the two descriptors.
5.  Closing `fd1` does not affect `fd2`, and `fd2` can still be used to perform I/O operations until it is also closed.

## How to Compile and Run
To compile the C source code and create the executable **`app`** binary:
```bash
$ gcc main.c -o app
