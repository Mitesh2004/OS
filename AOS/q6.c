#include <stdio.h>
#include <dirent.h>
#include <string.h>

int main(int c, char *v[]) {
    if(c!=2) return printf("Usage: %s <prefix>\n", v[0]),1;

    DIR *d = opendir(".");
    struct dirent *f;
    while((f = readdir(d))) {
        if(strncmp(f->d_name, v[1], strlen(v[1]))==0)
            puts(f->d_name);
    }
    closedir(d);
}

/*
m@Debian:~/Desktop/OS/MCS_Sem-1/denseVgolfed_code$ nano q6.c
m@Debian:~/Desktop/OS/MCS_Sem-1/denseVgolfed_code$ gcc q6.c
m@Debian:~/Desktop/OS/MCS_Sem-1/denseVgolfed_code$ ./a.out f
file_with_hole.txt
file2.txt
file1.txt
*/
