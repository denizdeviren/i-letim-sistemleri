#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "open_modes_test.txt"

void write_to_fd(int fd, const char *msg) {
    if (fd >= 0) {
        ssize_t len = strlen(msg);
        ssize_t bytes_written = write(fd, msg, len);
        if (bytes_written != len) {
            perror("write error");
        }
        close(fd);
    }
}

int main() {
    int fd;
    char *write_data = "--- New content ---\n";
    
    // --- 1. Salt Okuma Modu (Read Only) ---
    printf("1. Opening in Read Only (O_RDONLY) mode...\n");
    fd = open(FILENAME, O_RDONLY);
    
    if (fd < 0) {
        // Dosya yoksa veya okuma izni yoksa hata verir. Bu durumda dosyayı oluşturacağız.
        perror("open failed in O_RDONLY mode. Creating file...");
        // Dosyayı oluşturmak için O_CREAT ve salt yazma modunda açıyoruz.
        fd = open(FILENAME, O_WRONLY | O_CREAT, 0644);
        write_to_fd(fd, "Initial data.\n");
        printf("File created and written to. Now re-attempting O_RDONLY.\n");
        
        // Tekrar Salt Okuma modunda aç
        fd = open(FILENAME, O_RDONLY);
        if (fd >= 0) {
            printf("Successfully opened in O_RDONLY. FD: %d\n", fd);
            close(fd);
        } else {
             perror("Final open attempt failed.");
             exit(1);
        }
    } else {
        printf("Successfully opened in O_RDONLY. FD: %d\n", fd);
        close(fd);
    }

    // --- 2. Salt Yazma Modu (Write Only + Truncate) ---
    // O_TRUNC (mevcut içeriği siler) ve O_CREAT (yoksa oluşturur)
    printf("\n2. Opening in Write Only + Truncate (O_WRONLY | O_CREAT | O_TRUNC) mode...\n");
    fd = open(FILENAME, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    
    if (fd < 0) {
        perror("open error for O_WRONLY | O_TRUNC");
        exit(1);
    }
    printf("Successfully opened. Previous content is truncated (deleted). FD: %d\n", fd);
    write_to_fd(fd, "First write, this content replaces previous data.\n");


    // --- 3. Ekleme Modu (Append) ---
    // O_APPEND (yazma imlecini dosyanın sonuna konumlandırır)
    printf("\n3. Opening in Append (O_WRONLY | O_APPEND) mode...\n");
    fd = open(FILENAME, O_WRONLY | O_APPEND);

    if (fd < 0) {
        perror("open error for O_APPEND");
        exit(1);
    }
    printf("Successfully opened in O_APPEND. FD: %d\n", fd);
    write_to_fd(fd, write_data);
    printf("Content appended to the end of the file.\n");

    return 0;
}
