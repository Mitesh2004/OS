#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

int main(){
    pid_t pid=fork();
    if(pid<0) return perror("fork"),1;

    if(!pid){ // child
        while(1){ printf("Child (PID=%d) running...\n",getpid()); sleep(1); }
    } else {  // parent
        sleep(3);
        printf("Parent: Suspending child %d\n",pid); kill(pid,SIGSTOP);
        sleep(5);
        printf("Parent: Resuming child %d\n",pid); kill(pid,SIGCONT);
        sleep(3);
        printf("Parent: Killing child %d\n",pid); kill(pid,SIGKILL);
        wait(NULL);
        puts("Parent: Child terminated, exiting.");
    }
}
/*
m@Debian:~/Desktop/OS/MCS_Sem-1/golfed_code$ nano q28.c
m@Debian:~/Desktop/OS/MCS_Sem-1/golfed_code$ gcc q28.c
m@Debian:~/Desktop/OS/MCS_Sem-1/golfed_code$ ./a.out
Child (PID=3108) running...
Child (PID=3108) running...
Child (PID=3108) running...
Parent: Suspending child 3108
Parent: Resuming child 3108
Child (PID=3108) running...
Child (PID=3108) running...
Child (PID=3108) running...
Parent: Killing child 3108
Parent: Child terminated, exiting.
*/
/*
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }

    if (pid == 0) {
        // Child process: just prints messages continuously
        while (1) {
            printf("Child process (PID=%d) is running...\n", getpid());
            sleep(1);
        }
    } else {
        // Parent process
        sleep(3); // Let child run for a while

        printf("Parent: Suspending child (PID=%d)\n", pid);
        kill(pid, SIGSTOP); // suspend child

        sleep(5); // child is stopped during this time

        printf("Parent: Resuming child (PID=%d)\n", pid);
        kill(pid, SIGCONT); // resume child

        sleep(3);

        printf("Parent: Killing child (PID=%d)\n", pid);
        kill(pid, SIGKILL); // terminate child

        wait(NULL); // wait for child to exit
        printf("Parent: Child terminated, exiting.\n");
    }

    return 0;
}
*/
