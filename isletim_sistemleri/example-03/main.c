#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

int main() {
    int fd;
    char buffer[50];
    // Dosyaya yazılacak uzun bir içerik.
    char *full_data = "Operating System Concepts Lab: File Descriptor and lseek Demonstration.";
    ssize_t bytes_read, bytes_written;
    off_t offset;
    int data_length = strlen(full_data);

    // 1. Dosyayı Oku/Yaz izniyle oluştur veya aç
    fd = open("lseek_test.txt", O_CREAT | O_RDWR | O_TRUNC, 0644);

    if (fd < 0) {
        perror("open error");
        exit(1);
    }
    printf("File 'lseek_test.txt' opened (fd: %d).\n", fd);

    // 2. Dosyaya tüm veriyi yaz
    bytes_written = write(fd, full_data, data_length);
    printf("Wrote %zd bytes of data.\n", bytes_written);

    // 3. Dosya işaretçisini (offset) 13. karaktere konumlandır (lseek)
    // 13. karakter, "Concepts" kelimesinin 'C'sinden sonrasıdır.
    offset = lseek(fd, 13, SEEK_SET); 
    printf("File pointer repositioned to offset: %ld.\n", offset);

    // 4. Yeni konumdan itibaren dosyadan veri oku (read)
    // Okuma işlemi işaretçinin bulunduğu 13. pozisyondan başlayacaktır.
    bytes_read = read(fd, buffer, sizeof(buffer) - 1); 
    
    if (bytes_read > 0) {
        buffer[bytes_read] = '\0'; // Okunan veriyi null sonlandır
        printf("\nRead %zd bytes starting from offset %ld:\n", bytes_read, offset);
        printf("--- Content Read ---\n");
        printf("%s\n", buffer);
        printf("--------------------\n");
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
