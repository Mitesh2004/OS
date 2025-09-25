#include <stdio.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    struct stat st;
    for (int i = 1; i < argc; i++) {
        if (stat(argv[i], &st) == 0)
            printf("%s → inode: %lu\n", argv[i], st.st_ino);
        else
            perror(argv[i]);
    }
    return 0;
}

/*
m@Debian:~/Desktop/OS/MCS_Sem-1/denseVgolfed_code$ nano q2.c
m@Debian:~/Desktop/OS/MCS_Sem-1/denseVgolfed_code$ gcc q2.c
m@Debian:~/Desktop/OS/MCS_Sem-1/denseVgolfed_code$ ./a.out file1.txt file2.txt
file1.txt → inode: 23107061
file2.txt → inode: 23107063
*/
