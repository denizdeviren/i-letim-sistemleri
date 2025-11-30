# Example 05 – Advanced File Pointer Control with SEEK_CUR and SEEK_END

## Purpose
The main goal of this exercise is to demonstrate the advanced capabilities of the **`lseek()` system call** by utilizing its contextual reference points: **`SEEK_CUR`** (relative to the current file pointer) and **`SEEK_END`** (relative to the end of the file). This is essential for navigating files dynamically without knowing their exact structure beforehand.

## System Calls / Functions Used
- **`lseek()`**: Repositions the file offset for the open file descriptor.
- **`SEEK_CUR`**: The offset is calculated relative to the **current** position of the file pointer. A positive offset moves forward, a negative offset moves backward.
- **`SEEK_END`**: The offset is calculated relative to the **end** of the file. This is typically used to append data or, with an offset of 0, to determine the total file size.
- **`SEEK_SET`**: Used to reset the pointer to the beginning (offset 0) for repeated reads.
- **`open()`, `write()`, `read()`, `close()`**: Standard file I/O operations.

## How It Works
1.  A test file is opened, and a block of initial data is written.
2.  **`lseek(fd, 0, SEEK_END)`** is called. Since the offset is 0 and the reference is the end of the file, the return value is the total size of the file in bytes, effectively demonstrating how to find the file size.
3.  The pointer is reset to the beginning using `SEEK_SET`.
4.  The program reads the first 5 bytes. The file pointer automatically advances to position 5.
5.  **`lseek(fd, 10, SEEK_CUR)`** is called. It moves the pointer 10 bytes from its **current position (5)**, relocating it to position 15.
6.  A subsequent **`read()`** operation begins from this new position (15), showing that a section of the file was successfully skipped using the `SEEK_CUR` flag.

## How to Compile and Run
To compile the C source code and create the executable **`app`** binary:
```bash
$ gcc main.c -o app
