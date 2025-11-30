# Example 04 – Utilizing the open() System Call Modes

## Purpose
The objective of this lab is to explore the **`open()` system call** and, specifically, how different flags (or modes) passed as its second argument affect file access behavior in a Unix-like environment. Understanding these modes is essential for controlling Read/Write permissions and file creation/truncation policies.

## System Calls / Functions Used
- **`open()`**: The primary system call. It establishes a connection between a file and a process, returning a File Descriptor (FD). It takes the file path, access flags, and optionally, file permissions (`mode`).
- **`O_RDONLY`**: Flag to open a file for **read-only** access.
- **`O_WRONLY`**: Flag to open a file for **write-only** access.
- **`O_CREAT`**: Flag to **create** the file if it does not already exist. It requires a third argument (`mode`) to set file permissions (e.g., `0644`).
- **`O_TRUNC`**: Flag used with write access. If the file already exists, its length is **truncated (cleared) to zero**.
- **`O_APPEND`**: Flag used with write access. The file pointer is automatically positioned at the **end of the file** before every write operation.
- **`write()`**: Writes data to the file descriptor.
- **`close()`**: Closes the file descriptor.

## How It Works
1.  **Read-Only:** The program first attempts to open the file using **`O_RDONLY`**. If the file does not exist, this fails, demonstrating that `O_RDONLY` does not create the file.
2.  **Write Only (Truncate):** The file is opened with **`O_WRONLY | O_CREAT | O_TRUNC`**. This ensures that the file is created (if missing) and that any existing data is immediately deleted, resetting the file for new content.
3.  **Append Mode:** The file is then opened with **`O_WRONLY | O_APPEND`**. The `write()` operation in this mode automatically seeks to the end of the existing content before writing, allowing new data to be safely added without overwriting previous data.

## How to Compile and Run
To compile the C source code and create the executable **`app`** binary:
```bash
$ gcc main.c -o app
