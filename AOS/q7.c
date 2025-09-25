#include <stdio.h>
#include <dirent.h>

int main() {
    DIR *d = opendir(".");
    struct dirent *f;
    int count = 0;
    while((f = readdir(d))) {
        if(f->d_name[0] != '.') {  // skip hidden files
            puts(f->d_name);
            count++;
        }
    }
    closedir(d);
    printf("Total files: %d\n", count);
}
/*
m@Debian:~/Desktop/OS/MCS_Sem-1/denseVgolfed_code$ nano q7.c
m@Debian:~/Desktop/OS/MCS_Sem-1/denseVgolfed_code$ gcc q7.c
m@Debian:~/Desktop/OS/MCS_Sem-1/denseVgolfed_code$ ./a.out f
file_with_hole.txt
a.out
q6.c
q3.c
q5.c
q7.c
note
q2.c
q4.c
os_lab-book.pdf
file2.txt
q1.c
file1.txt
Total files: 13
*/

