/*Write a program that demonstrates the use of nice() system call. After a child process is
started using fork(), assign higher priority to the child using nice() system call.*/
// nice() +19 low to -20 high priority

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
    pid_t pid; // pid_t type of pid
    pid = fork();
    if (pid == 0)
    {
        // This is child
        printf("I am child Process. ID = %d\n", getpid());
        printf("priority = %d ,ID = %d\n", nice(-20), getpid());
    }
    else
    {
        // This is parent
        printf("I am parent Process. ID = %d\n", getpid());
        printf("priority = %d , ID = %d\n", nice(19), getpid());
    }
}

/*#include <sys/wait.h>
#include <errno.h>
int main()
{
    pid_t pid;
    int status;

    // Create child
    pid = fork();

    if (pid < 0)
    {
        // Fork failed
        fprintf(stderr, "Fork failed\n");
        return 1;
    }
    else if (pid == 0)
    {
        // This child
        printf("Child process before nice() PID: %d\n", getpid());

        // Increase the priority of the child
        int priority = nice(-40); // Decrease nice value to increase priority
        if (priority == -1 && errno != 0)
        {
            perror("nice");
            return 1;
        }

        printf("Child process after nice() New nice value: %d\n", priority);

        // Simulate some work
        for (int i = 0; i < 5; i++)
        {
            printf("Child process working........ %d\n", i);
            sleep(1);
        }

        return 0;
    }
    else
    {
        // This is parent
        printf("Parent process. PID: %d\n", getpid());
        printf("Parent process created child process with PID: %d\n", pid);

        // Wait for child to finish
        waitpid(pid, &status, 0);

        if (WIFEXITED(status))
        {
            printf("Child process exited with status %d\n", WEXITSTATUS(status));
        }
        else
        {
            printf("Child did not exit \n");
        }
    }

}
*/