#include <stdio.h>
#include <unistd.h>
#include <sys/types.h> 
int main() {
    pid_t pid = fork();
    printf("Before fork: This line is printed by the parent process.\n");
    if (pid < 0){ perror("fork failed"); return 1;}
    
    if (pid == 0) printf("Child process: My PID is %d, and my parent's PID is %d.\n", getpid(), getppid());
    else printf("Parent process: My PID is %d, and my child's PID is %d.\n", getpid(), pid);
    printf("After fork: This line is printed by both parent and child processes.\n");
    return 0;
}
