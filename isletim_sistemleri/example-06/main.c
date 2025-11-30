#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "dup_test.txt"

int main() {
    int fd1, fd2;
    ssize_t bytes_written;

    // 1. Dosyayı salt yazma ve oluşturma/silme modunda aç (open)
    // O_TRUNC: Mevcut içeriği siler.
    fd1 = open(FILENAME, O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (fd1 < 0) {
        perror("open error");
        exit(1);
    }
    printf("1. Original File Descriptor (fd1): %d\n", fd1);

    // 2. dup() ile dosya tanımlayıcısını kopyala
    // fd2, fd1'in kopyası olur.
    fd2 = dup(fd1);

    if (fd2 < 0) {
        perror("dup error");
        close(fd1);
        exit(1);
    }
    printf("2. Duplicated File Descriptor (fd2): %d\n", fd2);

    // 3. İlk FD (fd1) ile dosyaya yaz
    // İşaretçi, yazılan veri kadar ilerler.
    bytes_written = write(fd1, "Hello from fd1. ", 16);
    printf("3. fd1 used to write %zd bytes. \n", bytes_written);

    // 4. İkinci FD (fd2) ile dosyaya yaz
    // fd2, fd1 ile aynı dosya işaretçisini paylaştığı için yazma, fd1'in kaldığı yerden devam eder.
    bytes_written = write(fd2, "Hello from fd2. ", 16);
    printf("4. fd2 used to write %zd bytes. \n", bytes_written);
    
    // 5. fd1'i kapat
    close(fd1);
    printf("5. fd1 closed.\n");
    
    // 6. fd2 ile tekrar yazma denemesi
    // fd1 kapansa bile fd2 hala geçerli olduğu için yazma başarılı olur.
    bytes_written = write(fd2, "Still writing with fd2!\n", 23);
    printf("6. After fd1 closed, fd2 wrote %zd bytes.\n", bytes_written);

    // 7. fd2'yi kapat ve programı sonlandır
    close(fd2);
    printf("7. fd2 closed. Program finished.\n");

    return 0;
}
