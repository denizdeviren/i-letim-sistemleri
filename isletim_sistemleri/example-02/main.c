#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

int main() {
    int fd;
    char buffer[100];
    char *data = "This is the content written to the file using write() system call.";
    ssize_t bytes_read, bytes_written;

    // 1. Dosyayı Oku/Yaz izniyle oluştur veya aç (open)
    // O_CREAT: Dosya yoksa oluştur.
    // O_RDWR: Oku ve yaz.
    // 0644: Dosya izinleri (owner rw, group r, others r).
    fd = open("lab_data.txt", O_CREAT | O_RDWR, 0644);

    if (fd < 0) {
        perror("open error");
        exit(1);
    }

    // 2. Dosyaya veri yaz (write)
    bytes_written = write(fd, data, strlen(data));
    printf("Wrote %zd bytes to lab_data.txt.\n", bytes_written);

    // 3. Dosya işaretçisini (offset) başa al (lseek)
    // lseek(fd, offset, whence) - SEEK_SET: Dosyanın en başı.
    lseek(fd, 0, SEEK_SET);

    // 4. Dosyadan veri oku (read)
    bytes_read = read(fd, buffer, sizeof(buffer) - 1); // Güvenlik için 1 eksik oku
    
    if (bytes_read > 0) {
        buffer[bytes_read] = '\0'; // Okunan veriyi null sonlandır
        printf("Read %zd bytes from the file:\n", bytes_read);
        printf("Content: %s\n", buffer);
    } else {
        printf("Failed to read from the file.\n");
    }

    // 5. Dosyayı kapat (close)
    if (close(fd) < 0) {
        perror("close error");
        exit(1);
    }
    printf("File closed successfully.\n");

    return 0;
}
