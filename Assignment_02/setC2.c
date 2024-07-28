/*Write a C program that behaves like a shell which displays the command prompt ‘myshell$’. It
accepts the command, tokenize the command line and execute it by creating the child process.
Also implement the additional command ‘search’ as
myshell$ search f filename pattern : It will search the first occurrence of pattern in the given
file
myshell$ search a filename pattern : It will search all the occurrence of pattern in the given file
myshell$ search c filename pattern : It will count the number of occurrence of pattern in the
given file.*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

// Function to search for the pattern in the file
void search_file(const char *option, const char *filename, const char *pattern)
{
    FILE *file = fopen(filename, "r"); // Open the file for reading
    if (!file)
    {
        perror("Failed to open file"); // Print error if the file cannot be opened
        return;
    }

    char line[BUFFER_SIZE];
    int line_number = 0, count = 0;

    // Read the file line by line
    while (fgets(line, sizeof(line), file))
    {
        line_number++;
        char *pos = line;

        // Search for the pattern in the current line
        while ((pos = strstr(pos, pattern)) != NULL)
        {
            if (strcmp(option, "f") == 0)
            { // First occurrence
                printf("First occurrence at line %d: %s", line_number, line);
                fclose(file); // Close the file
                return;
            }
            else if (strcmp(option, "a") == 0)
            { // All occurrences
                printf("Occurrence at line %d: %s", line_number, line);
            }
            else if (strcmp(option, "c") == 0)
            { // Count occurrences
                count++;
            }
            pos += strlen(pattern); // Move to the next part of the line
        }
    }

    if (strcmp(option, "c") == 0)
    {
        printf("Total occurrences: %d\n", count); // Print the total count
    }

    fclose(file); // Close the file
}

int main()
{
    char line[BUFFER_SIZE];
    char *args[4]; // Array to store command and arguments
    char *token;

    while (1)
    {
        printf("myshellS$ "); // Display the shell prompt
        if (!fgets(line, sizeof(line), stdin))
            break; // Read the input

        // Remove newline character from the input line
        line[strcspn(line, "\n")] = '\0';

        // Tokenize the command line
        int i = 0;
        token = strtok(line, " ");
        while (token != NULL && i < 4)
        {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL; // Null-terminate the arguments array

        // Exit command to terminate the shell
        if (args[0] && strcmp(args[0], "exit") == 0)
            break;

        // Fork a child process to execute the command
        pid_t pid = fork();
        if (pid == -1)
        {
            perror("Fork failed"); // Print error if fork fails
            exit(1);
        }
        else if (pid == 0)
        {
            // Child process
            if (args[0] && strcmp(args[0], "search") == 0)
            {
                if (args[1] && args[2] && args[3])
                {
                    search_file(args[1], args[2], args[3]); // Call the search function
                }
                else
                {
                    printf("Usage: search <f|a|c> <filename> <pattern>\n"); // Print usage message
                }
                exit(0); // Exit the child process after completing the task
            }
            else
            {
                // Execute other commands
                execvp(args[0], args);   // Replace the child process with the new program
                perror("execvp failed"); // Print error if execvp fails
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

#define BUFFER_SIZE 1024

// Function to search for the pattern in the file
void search_file(const char *option, const char *filename, const char *pattern)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("Failed to open file");
        return;
    }

    char line[BUFFER_SIZE];
    int line_number = 0;
    int count = 0;

    while (fgets(line, sizeof(line), file))
    {
        line_number++;
        char *pos = line;
        int found = 0;

        while ((pos = strstr(pos, pattern)) != NULL)
        {
            found = 1;
            if (strcmp(option, "f") == 0)
            {
                printf("First occurrence at line %d: %s", line_number, line);
                fclose(file);
                return;
            }
            else if (strcmp(option, "a") == 0)
            {
                printf("Occurrence at line %d: %s", line_number, line);
                pos += strlen(pattern);
            }
            else if (strcmp(option, "c") == 0)
            {
                count++;
                pos += strlen(pattern);
            }
            else
            {
                printf("Invalid option for search\n");
                fclose(file);
                return;
            }
        }

        if (strcmp(option, "a") == 0 && found)
        {
            printf("Occurrence at line %d: %s", line_number, line);
        }
    }

    if (strcmp(option, "c") == 0)
    {
        printf("Total occurrences: %d\n", count);
    }

    fclose(file);
}

int main()
{
    char line[BUFFER_SIZE];
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
            if (args[0] != NULL && strcmp(args[0], "search") == 0)
            {
                if (args[1] != NULL && args[2] != NULL && args[3] != NULL)
                {
                    search_file(args[1], args[2], args[3]);
                }
                else
                {
                    printf("Usage: search <f|a|c> <filename> <pattern>\n");
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
*//////////////////////////////////////////////////////////////////////////////////////