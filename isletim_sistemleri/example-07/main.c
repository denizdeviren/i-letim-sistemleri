#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h> // wait() sistem çağrısı için gereklidir
#include <unistd.h>
#include <stdlib.h>

int main() {
    pid_t pid;
    int status;
    
    printf("Parent process started (PID: %d).\n", getpid());

    pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    } else if (pid == 0) {
        // Child Process
        printf("Child process created (PID: %d, PPID: %d).\n", getpid(), getppid());
        printf("Child is working for 3 seconds...\n");
        sleep(3); // 3 saniyelik bir iş simülasyonu
        printf("Child process finished its work and is exiting.\n");
        exit(0); // Alt süreç başarıyla sonlanır
    } else {
        // Parent Process
        printf("Parent is waiting for the child (Child PID: %d)...\n", pid);
        
        // wait() çağrısı: Alt süreç sonlanana kadar üst süreci bloklar.
        pid_t terminated_pid = wait(&status); 
        
        printf("Parent detected Child process termination (PID: %d).\n", terminated_pid);
        
        // Alt sürecin normal sonlanıp sonlanmadığını kontrol et
        if (WIFEXITED(status)) {
            printf("Child exited with status: %d\n", WEXITSTATUS(status));
        } else {
            printf("Child terminated abnormally.\n");
        }
        
        printf("Parent process finished its execution.\n");
    }

    return 0;
}
