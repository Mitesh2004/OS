#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

// Function to count characters, words, or lines in a file
void count(char c, char *fn)
{
    int lc = 0, wc = 0, cc = 0, handle;
    char ch;

    handle = open(fn, O_RDONLY);
    if (handle == -1)
        return;

    while (read(handle, &ch, 1) > 0)
    {
        cc++;
        if (ch == ' ' || ch == '\n') wc++;
        if (ch == '\n') lc++;
    }
    close(handle);

    if (c == 'c') printf("Total No. of Characters = %d\n", cc);
    else if (c == 'w') printf("Total No. of Words = %d\n", wc);
    else if (c == 'l') printf("Total No. of Lines = %d\n", lc);
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

        if (strcmp(cmd, "exit") == 0) break;

        n = sscanf(cmd, "%s %s %s", s1, s2, s3);

        if (n == 3 && strcmp(s1, "count") == 0)
        {
            count(s2[0], s3);
        }

        while (wait(NULL) > 0);
    }

    return 0;
}
