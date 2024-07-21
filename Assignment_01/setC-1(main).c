/*Implement the C program that accepts an integer array. Main function forks child
process. Parent process sorts an integer array and passes the sorted array to child process
through the command line arguments of execve() system call. The child process uses
execve() system call to load new program that uses this sorted array for performing the
binary search to search the particular item in the array.*/
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>

void bubbleSort(int a[], int n)
{
    int i, j, temp;
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (a[j] > a[j + 1])
            {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
}

int main()
{
    int n;
    printf("Enter the number of elements: ");
    scanf("%d", &n);
    int a[n];
    printf("Enter %d integers: ", n);
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &a[i]);
    }
    // Fork a child process
    pid_t pid = fork();
    if (pid == 0)
    {
        // Child process will just wait for the parent process to sort the array
        pause();
    }
    else if (pid > 0)
    {
        // Parent process: Sort the array
        bubbleSort(a, n);
        // Print the sorted array
        printf("Sorted array:");
        for (int i = 0; i < n; i++)
        {
            printf("%d ", a[i]);
        }
        printf("\n");
        // Create arguments for execve
        char *args[n + 2];
        args[0] = "./binary_search";
        for (int i = 0; i < n; ++i)
        {
            args[i + 1] = malloc(10);
            snprintf(args[i + 1], 10, "%d", a[i]);
        }
        args[n + 1] = NULL;
        // Send signal to child to continue
        kill(pid, SIGCONT);
        // Execute the child program with the sorted array
        execve("./binary_search", args, NULL);
        perror("execve"); // execve only returns on error
    }
    else
    {
        perror("Fork failed");
    }
}