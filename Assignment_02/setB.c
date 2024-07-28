/*Write a C program that behaves like a shell which displays the command prompt ‘myshell$’. It
accepts the command, tokenize the command line and execute it by creating the child process.
Also implement the additional command ‘list’ as
myshell$ list f dirname: It will display filenames in a given directory.
myshell$ list n dirname: It will count the number of entries in a given directory.
myshell$ list i dirname: It will display filenames and their inode number for the files in a given
directory.*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <dirent.h>
#include <sys/stat.h>

// Function to list files in a directory based on the given option
void list_directory(const char *option, const char *dirname)
{
    DIR *dir = opendir(dirname);   //DIR dirent.h
    if (dir == NULL)
    {
        perror("Failed to open directory");
        return;
    }

    struct dirent *entry;
    int count = 0;

    while ((entry = readdir(dir)) != NULL)
    {
        if (entry->d_name[0] == '.')   
        {
            continue; // Skip hidden files
        }
        if (strcmp(option, "f") == 0)
        {
            // Display filenames
            printf("%s\n", entry->d_name);
        }
        else if (strcmp(option, "n") == 0)
        {
            // Count number of entries
            count++;
        }
        else if (strcmp(option, "i") == 0)
        {
            // Display filenames and inode numbers
            printf("%s (inode: %ld)\n", entry->d_name, (long)entry->d_ino);
        }
        else
        {
            printf("Invalid option for list\n");
            closedir(dir);
            return;
        }
    }

    if (strcmp(option, "n") == 0)
    {
        printf("Total entries: %d\n", count);
    }

    closedir(dir);
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
            if (args[0] != NULL && strcmp(args[0], "list") == 0)
            {
                if (args[1] != NULL && args[2] != NULL)
                {
                    list_directory(args[1], args[2]);
                }
                else
                {
                    printf("Usage: list <f|n|i> <dirname>\n");
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
#include <sys/wait.h>
#include <dirent.h>
#include <sys/stat.h>

// Function to list files in a directory based on the given option
void list_directory(const char *option, const char *dirname)
{
    DIR *dir = opendir(dirname);
    if (!dir)
    {
        perror("Failed to open directory");
        return;
    }

    struct dirent *entry;
    int count = 0;

    while ((entry = readdir(dir)) != NULL)
    {
        if (entry->d_name[0] == '.')
            continue; // Skip hidden files

        if (strcmp(option, "f") == 0)
        {
            // Display filenames
            printf("%s\n", entry->d_name);
        }
        else if (strcmp(option, "n") == 0)
        {
            // Count number of entries
            count++;
        }
        else if (strcmp(option, "i") == 0)
        {
            // Display filenames and inode numbers
            printf("%s (inode: %ld)\n", entry->d_name, (long)entry->d_ino);
        }
        else
        {
            printf("Invalid option for list\n");
            closedir(dir);
            return;
        }
    }

    if (strcmp(option, "n") == 0)
        printf("Total entries: %d\n", count);
    closedir(dir);
}

int main()
{
    char line[1024];
    char *args[100];

    while (1)
    {
        printf("myshellS$ ");
        if (!fgets(line, sizeof(line), stdin))
            break; // Exit on EOF

        // Remove newline character from the input line
        line[strcspn(line, "\n")] = '\0';

        // Tokenize the command line
        int i = 0;
        char *token = strtok(line, " ");
        while (token)
        {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;

        // Check for the "exit" command
        if (args[0] && strcmp(args[0], "exit") == 0)
            break;

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
            if (args[0] && strcmp(args[0], "list") == 0)
            {
                if (args[1] && args[2])
                {
                    list_directory(args[1], args[2]);
                }
                else
                {
                    printf("Usage: list <f|n|i> <dirname>\n");
                }
                exit(0); // Exit after listing
            }
            else
            {
                // Execute other commands
                execvp(args[0], args);
                perror("execvp failed"); // If execvp returns, there was an error
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
*//////////////////////////////////////////////////////////////////////////////////////