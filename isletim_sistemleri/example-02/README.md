# Example 02 – Low-Level File I/O using System Calls

## Purpose
The main purpose of this exercise is to demonstrate and understand the fundamental **low-level file input/output (I/O)** operations in a Unix-like operating system using dedicated system calls (`open`, `read`, `write`, `close`). Unlike standard C library functions (e.g., `fopen`, `fprintf`), these calls interact directly with the kernel's file descriptor table.

## System Calls / Functions Used
- **`open()`**: Opens or creates a file, returning an integer file descriptor (`fd`) to the process.
- **`write()`**: Writes a specified number of bytes from a buffer to the file associated with the file descriptor.
- **`read()`**: Reads a specified number of bytes from the file associated with the file descriptor into a buffer.
- **`close()`**: Closes the file descriptor, releasing the system resource and making the file descriptor available for reuse.
- **`lseek()`**: Used to reposition the read/write file offset, which is necessary here to read the content written immediately before.
- **`perror()`**: Prints a system error message.
- **`exit()`**: Terminates the program execution.

## How It Works
1.  The **`open()`** call is used to create a file named `lab_data.txt` with read and write permissions (`O_RDWR` and `O_CREAT`). It returns a file descriptor (`fd`).
2.  The **`write()`** call is executed to write a pre-defined string into the file, starting at the current file offset (which is initially 0). The offset is moved forward after the write operation.
3.  The **`lseek()`** call is used with the `SEEK_SET` flag to explicitly reset the file offset back to the beginning of the file (position 0). This is crucial for reading the content just written.
4.  The **`read()`** call reads the content from the file into a local buffer.
5.  The read content is null-terminated and printed to the standard output.
6.  Finally, the **`close()`** call is used to terminate the connection between the process and the file, ensuring data integrity and freeing the file descriptor.

## How to Compile and Run
To compile the C source code and create the executable **`app`** binary:
```bash
$ gcc main.c -o app
