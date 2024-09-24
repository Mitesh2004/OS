#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
// #include <sys/wait.h>

void typeline(char *s, char *fn)
{
    int handle = open(fn, O_RDONLY);

    if (strcmp(s, "a") == 0)
    {
        char ch;
        while (read(handle, &ch, 1) > 0)
        {
            putchar(ch);
        }
    }
    else
    {
        int n = atoi(s);
        char ch;
        int lc = 0;

        if (n > 0)
        {
            while (read(handle, &ch, 1) > 0 && lc < n)
            {
                putchar(ch);
                if (ch == '\n')
                    lc++;
            }
        }
        else
        {
            // Count total lines
            int tl = 0;
            lseek(handle, 0, SEEK_SET);
            while (read(handle, &ch, 1) > 0)
            {
                if (ch == '\n')
                    tl++;
            }
            lseek(handle, 0, SEEK_SET); // Reset file offset

            // Skip lines and print the rest
            lc = tl + n; // Calculate lines to skip
            while (read(handle, &ch, 1) > 0)
            {
                if (lc <= 0)
                    putchar(ch);
                if (ch == '\n')
                    lc--;
            }
        }
    }
    close(handle);
}

int main()
{
    char cmd[80], s1[20], s2[20], s3[20];
    while (1)
    {
        printf("myShell$ ");
        fgets(cmd, 80, stdin);
        cmd[strcspn(cmd, "\n")] = 0;

        if (strcmp(cmd, "exit") == 0)
            break;

        cmd[strcspn(cmd, "\n")] = 0; // Remove newline
        int n = sscanf(cmd, "%s %s %s", s1, s2, s3);

        if (n == 3 && strcmp(s1, "typeline") == 0)
        {
            typeline(s2, s3);
        }
        // while (wait(NULL) > 0); // Wait for child processes
    }
    printf("Exiting myShell.\n");
    return 0;
}