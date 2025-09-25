#include <stdio.h>
#include <sys/stat.h>
#include <time.h>

int main(int c, char *v[]) {
    if (c!=2) return printf("Usage: %s <file>\n", v[0]),1;

    struct stat s;
    if (stat(v[1],&s)) return perror("stat"),1;

    printf("File: %s\nInode: %lu\nLinks: %lu\nSize: %ld bytes\n",v[1], s.st_ino, s.st_nlink, s.st_size);

    printf("Perms: ");
    for (int i=8;i>=0;i--)
        putchar((s.st_mode & (1<<i)) ? "rwxrwxrwx"[8-i] : '-');
    putchar('\n');

    printf("Access: %s", ctime(&s.st_atime));
    printf("Modify: %s", ctime(&s.st_mtime));
    printf("Change: %s", ctime(&s.st_ctime));
}

/*
m@Debian:~/Desktop/OS/MCS_Sem-1/denseVgolfed_code$ nano q3.c
m@Debian:~/Desktop/OS/MCS_Sem-1/denseVgolfed_code$ gcc q3.c
m@Debian:~/Desktop/OS/MCS_Sem-1/denseVgolfed_code$ ./a.out q1.c
File: q1.c
Inode: 23107059
Links: 1
Size: 621 bytes
Perms: rw-r--r--
Access: Fri Sep 19 21:23:39 2025
Modify: Fri Sep 19 21:23:35 2025
Change: Fri Sep 19 21:23:35 2025
*/
