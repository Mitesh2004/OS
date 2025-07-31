#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>
int main(){
    DIR *dir;
    struct dirent *entry;
    int FC=0;
    dir=opendir(".");
    if(dir==NULL){perror("opendir"); return 1;}
    printf("Files in the current directory.\n");
    while((entry=readdir(dir))!= NULL){ if(entry->d_type==DT_REG){printf("%s\n",entry->d_name); FC++;}}
    closedir(dir);
    printf("No. of files in the current dir. %d\n",FC);
    return 0;
}
