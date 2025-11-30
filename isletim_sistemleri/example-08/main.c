#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h> // waitpid() sistem çağrısı için gereklidir
#include <unistd.h>
#include <stdlib.h>

int main() {
    pid_t child1_pid, child2_pid;
    int status;
    
    printf("Parent process started (PID: %d).\n", getpid());

    // --- Birinci Alt Süreç Oluşturma ---
    child1_pid = fork();
    
    if (child1_pid < 0) {
        perror("fork child1 failed");
        exit(1);
    } else if (child1_pid == 0) {
        // Child 1 Process
        printf("[CHILD 1] PID: %d. Working for 3 seconds...\n", getpid());
        sleep(3); 
        printf("[CHILD 1] Finished work and exiting.\n");
        exit(10); // Farklı bir çıkış kodu
    }
    // Parent'ın Child 1'in PID'sini kaydettiği yer.

    // --- İkinci Alt Süreç Oluşturma ---
    child2_pid = fork(); 

    if (child2_pid < 0) {
        perror("fork child2 failed");
        // Hata durumunda diğer alt süreci temizle
        wait(NULL); 
        exit(1);
    } else if (child2_pid == 0) {
        // Child 2 Process
        printf("[CHILD 2] PID: %d. Working for 1 second...\n", getpid());
        sleep(1); 
        printf("[CHILD 2] Finished work and exiting.\n");
        exit(20); // Farklı bir çıkış kodu
    }
    // Parent'ın Child 2'nin PID'sini kaydettiği yer.

    // Parent Process
    printf("\n[PARENT] Child 1 PID: %d, Child 2 PID: %d\n", child1_pid, child2_pid);
    printf("[PARENT] Waiting ONLY for Child 1 to terminate...\n");
    
    // waitpid() çağrısı: SADECE child1_pid'nin sonlanmasını bekler.
    // waitpid(pid, &status, options)
    // child1_pid: Beklenecek sürecin PID'si
    // &status: Çıkış durumunun yazılacağı yer
    // 0: Varsayılan davranış (engelleme/blocking)
    pid_t terminated_pid = waitpid(child1_pid, &status, 0); 
    
    printf("\n[PARENT] waitpid() returned: %d\n", terminated_pid);
    
    if (terminated_pid == child1_pid) {
        printf("[PARENT] CONFIRMED: Child 1 (%d) terminated.\n", terminated_pid);
        if (WIFEXITED(status)) {
            printf("[PARENT] Child 1 Exit Status: %d\n", WEXITSTATUS(status));
        }
    }

    // Gerekirse diğer alt süreçleri de temizlemek için bir wait() çağrısı daha yapılır.
    printf("[PARENT] Cleaning up remaining child processes (Child 2)...\n");
    wait(NULL); 
    
    printf("[PARENT] Parent process finished execution.\n");

    return 0;
}
