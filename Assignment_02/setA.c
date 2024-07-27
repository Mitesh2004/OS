/*Write a C program that behaves like a shell which displays the command prompt ‘myshell$’. It
accepts the command, tokenize the command line and execute it by creating the child process.
Also implement the additional command ‘count’ as
myshell$ count c filename: It will display the number of characters in given file
myshell$ count w filename: It will display the number of words in given file
myshell$ count l filename: It will display the number of lines in given file
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

// Function to count characters, words, or lines in a file
void count_file(const char *option, const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("Failed to open file");
        return;
    }

    int count = 0;
    char c;
    int in_word = 0;

    // Loop through each character in the file
    while ((c = fgetc(file)) != EOF)
    {
        if (strcmp(option, "c") == 0)
        {
            // Count characters
            count++;
        }
        else if (strcmp(option, "w") == 0)
        {
            // Count words
            if (c == ' ' || c == '\n' || c == '\t')
            {
                in_word = 0;
            }
            else if (in_word == 0)
            {
                in_word = 1;
                count++;
            }
        }
        else if (strcmp(option, "l") == 0)
        {
            // Count lines
            if (c == '\n')
            {
                count++;
            }
        }
        else
        {
            printf("Invalid option for count\n");
            fclose(file);
            return;
        }
    }

    fclose(file);
    printf("Count: %d\n", count);
}

int main()
{
    char line[1024];
    char *args[100];
    char *token;

    while (1)
    {
        printf("myshellS$ ");
        if (fgets(line, sizeof(line), stdin) == NULL)
        {
            break; // Exit on EOF
        }

        // Remove newline character from the input line
        line[strcspn(line, "\n")] = '\0';

        // Tokenize the command line
        int i = 0;
        token = strtok(line, " ");
        while (token != NULL)
        {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;

        // Exit command to terminate the shell
        if (args[0] != NULL && strcmp(args[0], "exit") == 0)
        {
            break;
        }

        // Fork a child process to execute the command
        pid_t pid = fork();
        if (pid == -1)
        {
            perror("Fork failed");
            exit(1);
        }
        else if (pid == 0)
        {
            // Child process
            if (args[0] != NULL && strcmp(args[0], "count") == 0)
            {
                if (args[1] != NULL && args[2] != NULL)
                {
                    count_file(args[1], args[2]);
                }
                else
                {
                    printf("Usage: count <c|w|l> <filename>\n");
                }
                exit(0); // Child process should exit after completing the task
            }
            else
            {
                // Execute other commands
                execvp(args[0], args);
                // If execvp returns, there was an error
                perror("execvp failed");
                exit(1);
            }
        }
        else
        {
            // Parent process waits for the child to complete
            wait(NULL);
        }
    }

    return 0;
}



















/*/////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

// Function to separate tokens in the command line
void separate_tokens(char *cmd, char *tok[])
{
    int i = 0;
    char *p = strtok(cmd, " ");
    while (p != NULL)
    {
        tok[i++] = p;
        p = strtok(NULL, " ");
    }
    tok[i] = NULL;
}

// Function to count characters, words, or lines in a file
void count_file(char *type, char *fileName)
{
    int handle, count = 0;
    char ch;

    if ((handle = open(fileName, O_RDONLY)) == -1)
    {
        printf("%s not found\n", fileName);
        return;
    }

    if (strcmp(type, "c") == 0)
    {
        while (read(handle, &ch, 1) != 0)
        {
            count++;
        }
        printf("Number of characters: %d\n", count);
    }
    else if (strcmp(type, "w") == 0)
    {
        int in_word = 0;
        while (read(handle, &ch, 1) != 0)
        {
            if (ch == ' ' || ch == '\n' || ch == '\t')
            {
                if (in_word)
                {
                    count++;
                    in_word = 0;
                }
            }
            else
            {
                in_word = 1;
            }
        }
        if (in_word)
            count++; // Count the last word if it ends without a space
        printf("Number of words: %d\n", count);
    }
    else if (strcmp(type, "l") == 0)
    {
        while (read(handle, &ch, 1) != 0)
        {
            if (ch == '\n')
                count++;
        }
        printf("Number of lines: %d\n", count);
    }
    else
    {
        printf("Invalid count type. Use 'c' for characters, 'w' for words, or 'l' for lines.\n");
    }

    close(handle);
}

int main()
{
    char cmd[88], *args[10];
    int pid;
    system("clear");

    do
    {
        printf("\nmyshellS$ ");
        fgets(cmd, 80, stdin);
        cmd[strlen(cmd) - 1] = '\0';
        separate_tokens(cmd, args);

        if (strcmp(args[0], "count") == 0)
        {
            if (args[1] && args[2])
            {
                count_file(args[1], args[2]);
            }
            else
            {
                printf("Usage: count <c|w|l> <filename>\n");
            }
        }
        else
        {
            pid = fork();
            if (pid > 0)
            {
                wait(0);
            }
            else
            {
                if (execvp(args[0], args) == -1)
                {
                    printf("\nCommand %s not found\n", args[0]);
                }
            }
        }
    } while (1);

    return 0;
}
*/
/////////////////////////////////////////////////////////////////////////////////////