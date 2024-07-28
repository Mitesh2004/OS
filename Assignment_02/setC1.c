/*Write a C program that behaves like a shell which displays the command prompt ‘myshell$’. It
accepts the command, tokenize the command line and execute it by creating the child process.
Also implement the additional command ‘typeline’ as
myshell$ typeline n filename: It will display first n lines of the file.
myshell$ typeline -n filename: It will display last n lines of the file.
myshell$ typeline a filename: It will display all the lines of the file.*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <dirent.h>

// Function to display the first n lines of a file
void display_first_n_lines(const char *filename, int n)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("Failed to open file");
        return;
    }

    char line[1024];
    for (int i = 0; i < n && fgets(line, sizeof(line), file) != NULL; i++)
    {
        printf("%s", line);
    }

    fclose(file);
}

// Function to display the last n lines of a file
void display_last_n_lines(const char *filename, int n)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("Failed to open file");
        return;
    }

    // Count total lines in file
    int total_lines = 0;
    char line[1024];
    while (fgets(line, sizeof(line), file) != NULL)
    {
        total_lines++;
    }

    // Reset file pointer to beginning
    fseek(file, 0, SEEK_SET);

    // Skip lines until the last n lines
    int skip_lines = total_lines > n ? total_lines - n : 0;
    for (int i = 0; i < skip_lines && fgets(line, sizeof(line), file) != NULL; i++)
        ;

    // Print the last n lines
    while (fgets(line, sizeof(line), file) != NULL)
    {
        printf("%s", line);
    }

    fclose(file);
}

// Function to display all lines of a file
void display_all_lines(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("Failed to open file");
        return;
    }

    char line[1024];
    while (fgets(line, sizeof(line), file) != NULL)
    {
        printf("%s", line);
    }

    fclose(file);
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
            if (args[0] != NULL && strcmp(args[0], "typeline") == 0)
            {
                if (args[1] != NULL && args[2] != NULL)
                {
                    if (strcmp(args[1], "a") == 0)
                    {
                        display_all_lines(args[2]);
                    }
                    else if (args[1][0] == '-')
                    {
                        int n = atoi(args[1] + 1);
                        display_last_n_lines(args[2], n);
                    }
                    else
                    {
                        int n = atoi(args[1]);
                        display_first_n_lines(args[2], n);
                    }
                }
                else
                {
                    printf("Usage: typeline <n|-n|a> <filename>\n");
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
