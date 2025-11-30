#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

#define FILENAME "seek_cur_end_test.txt"

int main() {
    int fd;
    char read_buffer[20];
    off_t current_offset;
    ssize_t bytes_read;
    
    // Uzun başlangıç verisi (toplam 30 karakter)
    char *initial_data = "AAAABBBBCCCCDDDDEEEEFFFFGGGGHHHH"; 
    int initial_len = strlen(initial_data);

    // 1. Dosyayı oluştur ve aç (open)
    fd = open(FILENAME, O_CREAT | O_RDWR | O_TRUNC, 0644);

    if (fd < 0) {
        perror("open error");
        exit(1);
    }
    printf("1. File opened and truncated (fd: %d).\n", fd);

    // 2. Dosyaya tüm veriyi yaz (write)
    write(fd, initial_data, initial_len);
    printf("2. Wrote %d bytes of initial data.\n", initial_len);

    // 3. SEEK_END kullanarak dosya boyutunu bulma
    current_offset = lseek(fd, 0, SEEK_END);
    printf("3. File size found using SEEK_END: %ld bytes.\n", current_offset);

    // 4. Okuma için işaretçiyi dosyanın başına getir
    lseek(fd, 0, SEEK_SET);

    // 5. İlk 5 karakteri oku
    bytes_read = read(fd, read_buffer, 5); 
    read_buffer[bytes_read] = '\0';
    printf("\n5. Read %zd bytes (First 5): %s\n", bytes_read, read_buffer);
    // İşaretçi şu an 5. pozisyonda.

    // 6. SEEK_CUR kullanarak mevcut konumdan 10 karakter atla
    current_offset = lseek(fd, 10, SEEK_CUR); 
    printf("6. Skipped 10 characters using SEEK_CUR. New offset: %ld.\n", current_offset); 
    // İşaretçi şimdi 5 + 10 = 15. pozisyonda.

    // 7. Yeni konumdan itibaren 10 karakter oku
    bytes_read = read(fd, read_buffer, 10);
    read_buffer[bytes_read] = '\0';
    printf("7. Read %zd bytes (Skipped 10 from current): %s\n", bytes_read, read_buffer);
    // Okuyağımız kısım: "DDDEEEEFFF" (15. pozisyondan itibaren)

    // 8. Dosyayı kapat
    close(fd);
    printf("\n8. File closed successfully.\n");

    return 0;
}
