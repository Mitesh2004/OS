#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <stdlib.h>

int main(int c,char *v[]){
    if(c!=2) return printf("Usage: %s <month 1-12>\n",v[0]),1;
    int m=atoi(v[1]); if(m<1||m>12) return printf("Invalid month!\n"),1;

    DIR *d=opendir("."); struct dirent *e; struct stat s;
    while((e=readdir(d))){
        if(stat(e->d_name,&s)) continue;
        if(localtime(&s.st_mtime)->tm_mon+1==m) printf("%s\n",e->d_name);
    }
    closedir(d);
}
/*
m@Debian:~/Desktop/OS/MCS_Sem-1/golfed_code$ nano q9.c
m@Debian:~/Desktop/OS/MCS_Sem-1/golfed_code$ gcc q9.c
m@Debian:~/Desktop/OS/MCS_Sem-1/golfed_code$ ./a.out 9
file_with_hole.txt
a.out
q6.c
q9.c
q3.c
tPwME.txt
q5.c
q7.c
note
..
q2.c
q4.c
os_lab-book.pdf
q8.c
file2.txt
q1.c
file1.txt
.
*/

/*
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <stdlib.h>

int main(int c, char *v[]) {
    if(c != 2) return printf("Usage: %s <month 1-12>\n", v[0]), 1;

    int m = atoi(v[1]);
    if(m < 1 || m > 12) return printf("Invalid month!\n"), 1;

    DIR *d = opendir(".");
    if(!d) return printf("Failed to open directory.\n"), 1;

    struct dirent *e;
    struct stat s;
    int found = 0;  // Flag to track if any file was found

    while((e = readdir(d))) {
        if(stat(e->d_name, &s)) continue;
        if(localtime(&s.st_mtime)->tm_mon + 1 == m) {
            printf("%s\n", e->d_name);
            found = 1;  // Mark that at least one file was found
        }
    }

    closedir(d);

    if(!found) {
        printf("No files were created in month %d.\n", m);
    }

    return 0;
}
*/

/*
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) return printf("Usage: %s <month number 1-12>\n", argv[0]), 1;

    int month = atoi(argv[1]);
    if (month < 1 || month > 12) return printf("Invalid month!\n"), 1;

    DIR *d = opendir(".");
    if (!d) return perror("opendir"), 1;

    struct dirent *entry;
    struct stat st;
    while ((entry = readdir(d)) != NULL) {
        if (stat(entry->d_name, &st) == 0) {
            struct tm *tm_info = localtime(&st.st_mtime);
            if (tm_info->tm_mon + 1 == month)  // tm_mon: 0-11
                printf("%s\n", entry->d_name);
        }
    }

    closedir(d);
    return 0;
}
*/
