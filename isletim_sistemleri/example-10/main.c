#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h> // wait() çağrısı kullanılmasa bile süreç yönetimi için dahil edildi.

int main() {
    pid_t pid;
    
    printf("[PARENT] Parent process started (PID: %d).\n", getpid());

    pid = fork();

    if (pid < 0) {
        perror("fork error");
        exit(1);
    } else if (pid == 0) {
        // Child Process
        printf("[CHILD] PID: %d, PPID: %d.\n", getpid(), getppid());
        printf("[CHILD] Child is exiting immediately (Will become a Zombie).\n");
        // Alt süreç hemen sonlanır.
        exit(0); 
    } else {
        // Parent Process
        printf("[PARENT] Child PID: %d created.\n", pid);
        // Parent, alt süreci beklemek için wait() çağırmaz.
        printf("[PARENT] Parent is sleeping for 10 seconds (Zombie will be visible).\n");
        
        sleep(10); // Parent, alt süreçten daha uzun yaşar ancak onu temizlemez.
        
        printf("[PARENT] Parent woke up. The child process (PID: %d) is now a Zombie.\n", pid);
        printf("[PARENT] Parent process finished its execution and is now exiting.\n");
        
        // NOT: Programı bu noktada sonlandırdığınızda (parent exit), işletim sistemi 
        // otomatik olarak zombi süreci temizleyecektir (init'e bağlanır ve temizlenir).
    }

    return 0;
}
