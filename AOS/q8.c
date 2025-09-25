#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>

typedef struct { char *n; off_t s; } F;

int cmp(const void *a,const void *b){ return ((F*)a)->s - ((F*)b)->s; }

int main(int c,char *v[]){
    if(c<2) return printf("Usage: %s <files>\n",v[0]),1;
    F f[c-1]; struct stat st;
    for(int i=1;i<c;i++) f[i-1]=(stat(v[i],&st)?(F){v[i],-1}:(F){v[i],st.st_size});
    qsort(f,c-1,sizeof(F),cmp);
    for(int i=0;i<c-1;i++) if(f[i].s>=0) printf("%s (%ld bytes)\n",f[i].n,(long)f[i].s);
}
/*
m@Debian:~/Desktop/OS/MCS_Sem-1/golfed_code$ nano q8.c
m@Debian:~/Desktop/OS/MCS_Sem-1/golfed_code$ gcc q8.c
m@Debian:~/Desktop/OS/MCS_Sem-1/golfed_code$ ./a.out q1.c q2.c q3.c q4.c q5.c
q5.c (522 bytes)
q2.c (565 bytes)
q1.c (621 bytes)
q3.c (957 bytes)
q4.c (1207 bytes)
*/

/*
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>

struct File { char *n; off_t s; };

int cmp(const void *a,const void *b){ 
    return ((struct File*)a)->s - ((struct File*)b)->s; 
}

int main(int c,char *v[]){
    if(c<2) return printf("Usage: %s <files>\n",v[0]),1;
    struct File f[c-1]; struct stat st;
    for(int i=1;i<c;i++) f[i-1]=(stat(v[i],&st)?(struct File){v[i],-1}:(struct File){v[i],st.st_size});
    qsort(f,c-1,sizeof(struct File),cmp);
    for(int i=0;i<c-1;i++) if(f[i].s>=0) printf("%s (%ld bytes)\n",f[i].n,(long)f[i].s);
}
*/

/*
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

struct FileInfo {
    char *name;
    off_t size;
};

int cmp(const void *a, const void *b) {
    const struct FileInfo *fa = a, *fb = b;
    if (fa->size < fb->size) return -1;
    if (fa->size > fb->size) return 1;
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc < 2) return printf("Usage: %s <file1> <file2> ...\n", argv[0]), 1;

    int n = argc - 1;
    struct FileInfo files[n];
    struct stat st;

    for (int i = 0; i < n; i++) {
        if (stat(argv[i+1], &st) == 0) {
            files[i].name = argv[i+1];
            files[i].size = st.st_size;
        } else {
            perror(argv[i+1]);
            files[i].name = argv[i+1];
            files[i].size = -1; // mark invalid
        }
    }

    qsort(files, n, sizeof(struct FileInfo), cmp);

    printf("Files in ascending order of size:\n");
    for (int i = 0; i < n; i++) {
        if (files[i].size >= 0)
            printf("%s (%ld bytes)\n", files[i].name, (long)files[i].size);
    }

    return 0;
}
*/
