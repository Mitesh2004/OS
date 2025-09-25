#include <stdio.h>
#include <sys/stat.h>

int main(int c,char *v[]){
    if(c!=2) return printf("Usage: %s <file>\n",v[0]),1;
    struct stat s; if(stat(v[1],&s)<0) return perror("stat"),1;
    printf("File: %s\nType: ",v[1]);
    if(S_ISREG(s.st_mode)) puts("Regular file");
    else if(S_ISDIR(s.st_mode)) puts("Directory");
    else if(S_ISCHR(s.st_mode)) puts("Character device");
    else if(S_ISBLK(s.st_mode)) puts("Block device");
    else if(S_ISFIFO(s.st_mode)) puts("FIFO / Pipe");
    else if(S_ISLNK(s.st_mode)) puts("Symbolic link");
    else if(S_ISSOCK(s.st_mode)) puts("Socket");
    else puts("Unknown");
}
/*
m@Debian:~/Desktop/OS/MCS_Sem-1/golfed_code$ nano q14.c
m@Debian:~/Desktop/OS/MCS_Sem-1/golfed_code$ gcc q14.c
m@Debian:~/Desktop/OS/MCS_Sem-1/golfed_code$ ./a.out ..
File: ..
Type: Directory
m@Debian:~/Desktop/OS/MCS_Sem-1/golfed_code$ ./a.out .
File: .
Type: Directory
m@Debian:~/Desktop/OS/MCS_Sem-1/golfed_code$ ./a.out q1
stat: No such file or directory
m@Debian:~/Desktop/OS/MCS_Sem-1/golfed_code$ ./a.out q1.c
File: q1.c
Type: Regular file
m@Debian:~/Desktop/OS/MCS_Sem-1/golfed_code$ ./a.out mango
File: mango
Type: Directory
m@Debian:~/Desktop/OS/MCS_Sem-1/golfed_code$ ./a.out /etc
File: /etc
Type: Directory
*/

/*
#include <stdio.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    if (argc != 2) return printf("Usage: %s <filename>\n", argv[0]), 1;

    struct stat st;
    if (stat(argv[1], &st) < 0) {
        perror("stat");
        return 1;
    }

    printf("File: %s\nType: ", argv[1]);

    if (S_ISREG(st.st_mode))   printf("Regular file\n");
    else if (S_ISDIR(st.st_mode))  printf("Directory\n");
    else if (S_ISCHR(st.st_mode))  printf("Character device\n");
    else if (S_ISBLK(st.st_mode))  printf("Block device\n");
    else if (S_ISFIFO(st.st_mode)) printf("FIFO / Pipe\n");
    else if (S_ISLNK(st.st_mode))  printf("Symbolic link\n");
    else if (S_ISSOCK(st.st_mode)) printf("Socket\n");
    else printf("Unknown\n");

    return 0;
}
*/
