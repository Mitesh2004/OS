#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

void list(char option, char *dirName)
{
    DIR *dir = opendir(dirName);
    struct dirent *entry;
    struct stat buff;
    int count = 0;

    while ((entry = readdir(dir)) != NULL)
    {
        if (option == 'f')  // List filenames
            printf("%s\n", entry->d_name);
        else if (option == 'n')  // Count entries
            count++;
        else if (option == 'i')  // List filenames with inodes
        {
            stat(entry->d_name, &buff);
            printf("%s\t%ld\n", entry->d_name, (long)buff.st_ino);
        }
    }

    if (option == 'n')
        printf("Total No. of Entries = %d\n", count);

    closedir(dir);
}

int main()
{
    char cmd[80], s1[20], s2[20], s3[20];
    int n;
    
    system("clear");

    while (1)
    {
        printf("myShell$ ");
        fgets(cmd, 80, stdin);
        cmd[strcspn(cmd, "\n")] = 0;

        if (strcmp(cmd, "exit") == 0)
            break;
            
        n = sscanf(cmd, "%s %s %s", s1, s2, s3);
        
        if (n == 3 && strcmp(s1, "list") == 0)
            list(s2[0], s3);
        else
            printf("Usage: list <option> <directory>\n");
    }

    return 0;
}