#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdlib.h>

int main(int c,char *v[]){
    if(c!=2) return printf("Usage: %s <size in bytes>\n",v[0]),1;
    long n=atol(v[1]); DIR *d=opendir("."); struct dirent *e; struct stat s;
    while((e=readdir(d))){
        if(stat(e->d_name,&s)==0 && s.st_size>n)
            printf("%s (%ld bytes)\n",e->d_name,(long)s.st_size);
    }
    closedir(d);
}
/*
m@Debian:~/Desktop/OS/MCS_Sem-1/golfed_code$ nano 10.c
m@Debian:~/Desktop/OS/MCS_Sem-1/golfed_code$ gcc 10.c
m@Debian:~/Desktop/OS/MCS_Sem-1/golfed_code$ ./a.out 100
file_with_hole.txt (10010 bytes)
a.out (16216 bytes)
q6.c (565 bytes)
q9.c (2377 bytes)
q3.c (957 bytes)
10.c (983 bytes)
tPwME.txt (2553 bytes)
q5.c (522 bytes)
q7.c (638 bytes)
note (650 bytes)
.. (4096 bytes)
q2.c (565 bytes)
q4.c (1207 bytes)
os_lab-book.pdf (288352 bytes)
q8.c (2407 bytes)
q1.c (621 bytes)
. (4096 bytes)
m@Debian:~/Desktop/OS/MCS_Sem-1/golfed_code$ ./a.out 1000
file_with_hole.txt (10010 bytes)
a.out (16216 bytes)
q9.c (2377 bytes)
tPwME.txt (2553 bytes)
.. (4096 bytes)
q4.c (1207 bytes)
os_lab-book.pdf (288352 bytes)
q8.c (2407 bytes)
. (4096 bytes)
*/


/*
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) return printf("Usage: %s <size in bytes>\n", argv[0]), 1;

    long n = atol(argv[1]);
    DIR *d = opendir(".");
    if (!d) return perror("opendir"), 1;

    struct dirent *entry;
    struct stat st;
    while ((entry = readdir(d)) != NULL) {
        if (stat(entry->d_name, &st) == 0 && st.st_size > n)
            printf("%s (%ld bytes)\n", entry->d_name, (long)st.st_size);
    }

    closedir(d);
    return 0;
}
*/
