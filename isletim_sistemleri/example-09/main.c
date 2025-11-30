#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h> // Gerekli olmasa da süreç yönetimi için dahil edildi.

int main() {
    pid_t pid;

    printf("[PARENT] Parent process started (PID: %d).\n", getpid());

    pid = fork();

    if (pid < 0) {
        perror("fork error");
        exit(1);
    } else if (pid == 0) {
        // Child Process
        printf("\n[CHILD] PID: %d, Initial PPID: %d\n", getpid(), getppid());
        printf("[CHILD] Parent will now exit. Child is going to sleep for 5 seconds...\n");
        
        sleep(5); // Alt süreç 5 saniye boyunca çalışmaya devam ederken üst süreç sonlanır.
        
        // Uyandıktan sonra, alt süreç ebeveynini tekrar kontrol eder.
        printf("\n[CHILD] After 5 seconds, checking PPID again.\n");
        // PPID, init (veya modern sistemlerde systemd/upstart) sürecinin PID'si olan 1 olacaktır.
        printf("[CHILD] New PPID: %d (Orphan Process adopted by init).\n", getppid()); 
        printf("[CHILD] Child process finished.\n");
        exit(0);
    } else {
        // Parent Process
        printf("[PARENT] Parent PID: %d, Child PID: %d\n", getpid(), pid);
        printf("[PARENT] Parent is exiting immediately (without wait()).\n");
        
        // Parent hemen sonlanır, alt süreci yetim bırakır.
        exit(0); 
    }

    return 0;
}
