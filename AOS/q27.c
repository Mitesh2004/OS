#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void h(int s){ puts("Parent: Alarm fired (SIGALRM received from child)"); }

int main(){
    pid_t pid=fork();
    if(pid<0) return perror("fork"),1;

    if(!pid){ // child
        sleep(3);
        printf("Child: Sending SIGALRM to parent (PID=%d)\n",getppid());
        kill(getppid(),SIGALRM);
        exit(0);
    } else {  // parent
        signal(SIGALRM,h);
        puts("Parent: Waiting for alarm...");
        pause();        // wait for SIGALRM
        wait(NULL);     // wait for child
        puts("Parent: Child terminated. Exiting.");
    }
}
/*
m@Debian:~/Desktop/OS/MCS_Sem-1/golfed_code$ nano q27.c
m@Debian:~/Desktop/OS/MCS_Sem-1/golfed_code$ nano q27.c
m@Debian:~/Desktop/OS/MCS_Sem-1/golfed_code$ gcc q27.c
m@Debian:~/Desktop/OS/MCS_Sem-1/golfed_code$ ./a.out
Parent: Waiting for alarm...
Child: Sending SIGALRM to parent (PID=3067)
Parent: Alarm fired (SIGALRM received from child)
Parent: Child terminated. Exiting.
*/
/*
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

// Signal handler for parent
void alarm_handler(int sig) {
    if (sig == SIGALRM) {
        printf("Parent: Alarm is fired (SIGALRM received from child)\n");
    }
}

int main() {
    pid_t pid;
    pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }

    if (pid == 0) {
        // Child process
        sleep(3);  // wait before firing alarm
        printf("Child: Sending SIGALRM to parent (PID=%d)\n", getppid());
        kill(getppid(), SIGALRM);
        exit(0);
    } else {
        // Parent process
        signal(SIGALRM, alarm_handler); // catch SIGALRM
        printf("Parent: Waiting for alarm...\n");

        pause(); // wait until signal is received

        wait(NULL); // wait for child to terminate
        printf("Parent: Child terminated. Exiting.\n");
    }

    return 0;
}
*/
