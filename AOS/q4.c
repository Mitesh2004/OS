/*
#include <stdio.h>
#include <stdlib.h>

int main(int c,char *v[]){
    if(c!=2) return printf("Usage: %s <file>\n",v[0]),1;

    char cmd[256];
    snprintf(cmd,sizeof(cmd),"file -b %s",v[1]);
    return system(cmd);
}
*/

#include <stdio.h>
#include <sys/stat.h>

int main(int c,char *v[]){
    if(c!=2) return printf("Usage: %s <file>\n",v[0]),1;

    struct stat s;

    if(stat(v[1],&s)) return perror("stat"),1;

    if(S_ISREG(s.st_mode))  puts("Regular file");
    else if(S_ISDIR(s.st_mode))  puts("Directory");
    else if(S_ISLNK(s.st_mode))  puts("Symbolic link");
    else if(S_ISCHR(s.st_mode))  puts("Character device");
    else if(S_ISBLK(s.st_mode))  puts("Block device");
    else if(S_ISFIFO(s.st_mode)) puts("FIFO/pipe");
    else if(S_ISSOCK(s.st_mode)) puts("Socket");
    else puts("Unknown");
}

/*
@Debian:~/Desktop/OS/MCS_Sem-1/denseVgolfed_code$ nano q4.c
m@Debian:~/Desktop/OS/MCS_Sem-1/denseVgolfed_code$ gcc q4.c
m@Debian:~/Desktop/OS/MCS_Sem-1/denseVgolfed_code$ ./a.out q1.c
Regular file
m@Debian:~/Desktop/OS/MCS_Sem-1/denseVgolfed_code$ ./a.out file1.c
stat: No such file or directory
m@Debian:~/Desktop/OS/MCS_Sem-1/denseVgolfed_code$ ./a.out file1.txt
Regular file
*/
