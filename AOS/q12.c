#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

int cmp(const void *a,const void *b){ return strcmp(*(char**)a,*(char**)b); }

int main(){
    DIR *d=opendir("."); if(!d) return perror("opendir"),1;
    struct dirent *e; char *dirs[1000]; int n=0; struct stat s;
    while((e=readdir(d)))
        if(stat(e->d_name,&s)==0 && S_ISDIR(s.st_mode)) dirs[n++]=strdup(e->d_name);
    closedir(d);
    qsort(dirs,n,sizeof(char*),cmp);
    for(int i=0;i<n;i++) printf("%s\n",dirs[i]),free(dirs[i]);
}
/*
m@Debian:~/Desktop/OS/MCS_Sem-1/golfed_code$ nano q12.c
m@Debian:~/Desktop/OS/MCS_Sem-1/golfed_code$ gcc q12.c
m@Debian:~/Desktop/OS/MCS_Sem-1/golfed_code$ ./a.out
.
..
apple
blueberry
mango
orange
strawberry
*/
/*
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>

int cmp(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

int main() {
    DIR *d = opendir(".");
    if (!d) return perror("opendir"), 1;

    struct dirent *entry;
    char *dirs[1000];  // max 1000 subdirectories
    int count = 0;

    while ((entry = readdir(d)) != NULL) {
        struct stat st;
        if (stat(entry->d_name, &st) == 0 && S_ISDIR(st.st_mode)) {
            dirs[count] = strdup(entry->d_name);
            count++;
        }
    }
    closedir(d);

    qsort(dirs, count, sizeof(char *), cmp);

    printf("Subdirectories in alphabetical order:\n");
    for (int i = 0; i < count; i++) {
        printf("%s\n", dirs[i]);
        free(dirs[i]);
    }

    return 0;
}
*/
