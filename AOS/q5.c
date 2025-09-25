#include <stdio.h>

int main(int c, char *v[]) {
    if(c != 2) return printf("Usage: %s <file>\n", v[0]),1;

    FILE *f = fopen(v[1], "r");
    if(f) printf("File exists\n"), fclose(f);
    else   printf("File not found\n");
}
/*
m@Debian:~/Desktop/OS/MCS_Sem-1/denseVgolfed_code$ nano q5.c
m@Debian:~/Desktop/OS/MCS_Sem-1/denseVgolfed_code$ gcc q5.c
m@Debian:~/Desktop/OS/MCS_Sem-1/denseVgolfed_code$ ./a.out file1.txt
File exists
m@Debian:~/Desktop/OS/MCS_Sem-1/denseVgolfed_code$ ./a.out file10.txt
File not found
*/
