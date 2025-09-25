#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int fd = open("file_with_hole.txt", O_WRONLY | O_CREAT, 0644);

/*    if (fd < 0) {
        perror("open");
        return 1;
    }
*/
    write(fd, "Hello", 5);         // write first 5 bytes
    lseek(fd, 10000, SEEK_CUR);    // create a hole (skip 10KB)(1KB=1000)
    write(fd, "World", 5);         // write after the hole

    close(fd);
    return 0;
}

/*
m@Debian:~/Desktop/OS/MCS_Sem-1/denseVgolfed_code$ nano q1.c
m@Debian:~/Desktop/OS/MCS_Sem-1/denseVgolfed_code$ gcc q1.c
m@Debian:~/Desktop/OS/MCS_Sem-1/denseVgolfed_code$ ./a.out
*/
