#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    pid_t pid;

    // Create a new process
    printf("Before fork: Parent PID is %d\n", getpid());
    pid = fork();

    if (pid < 0) {
        // Error occurred
        perror("fork");
        exit(1);
    } else if (pid == 0) {
        // Child process execution path (fork returns 0 to the child)
        printf("\n--- CHILD PROCESS ---\n");
        printf("Child PID: %d\n", getpid());
        printf("Parent PID (PPID): %d\n", getppid());
        printf("Child process finished.\n");
    } else {
        // Parent process execution path (fork returns child's PID to the parent)
        // In this simple example, we let the parent continue without waiting.
        printf("\n--- PARENT PROCESS ---\n");
        printf("Parent PID: %d\n", getpid());
        printf("Child PID (returned by fork): %d\n", pid);
        printf("Parent process finished.\n");
    }

    return 0;
}
