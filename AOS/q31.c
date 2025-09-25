#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

pid_t cpid;
void t(int s){ printf("Child did not finish in 5 sec. Killing child...\n"); kill(cpid,SIGKILL); }

int main(){
    signal(SIGALRM,t);
    if((cpid=fork())==0) execlp("sleep","sleep","10",NULL),exit(1);
    alarm(5);
    int st; waitpid(cpid,&st,0);
    printf(WIFEXITED(st) ? "Child exited normally: %d\n" : "Child killed by signal %d\n",
           WIFEXITED(st) ? WEXITSTATUS(st) : WTERMSIG(st));
    printf("Parent exiting.\n");
}
/*
m@Debian:~/Desktop/OS/MCS_Sem-1/golfed_code$ nano q31.c
m@Debian:~/Desktop/OS/MCS_Sem-1/golfed_code$ gcc q31.c
m@Debian:~/Desktop/OS/MCS_Sem-1/golfed_code$ ./a.out
Child did not finish in 5 sec. Killing child...
Child killed by signal 9
Parent exiting.
*/
/*
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

pid_t cpid;

void ch(int s){
    int st;
    if(waitpid(cpid,&st,WNOHANG)>0){
        if(WIFEXITED(st)) printf("Child exited normally: %d\n",WEXITSTATUS(st));
        else if(WIFSIGNALED(st)) printf("Child killed by signal %d\n",WTERMSIG(st));
    }
}

void al(int s){ printf("Child did not finish in 5 sec. Killing child...\n"); kill(cpid,SIGKILL); }

int main(){
    signal(SIGCHLD,ch); signal(SIGALRM,al);

    cpid=fork();
    if(cpid<0) return perror("fork"),1;

    if(!cpid){ execlp("sleep","sleep","10",NULL); perror("execlp"); exit(1); }
    else{ alarm(5); pause(); printf("Parent exiting.\n"); }
}
*/
/*
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

pid_t child_pid;

// Handler for SIGCHLD
void child_handler(int sig) {
    int status;
    pid_t pid = waitpid(child_pid, &status, WNOHANG);
    if (pid > 0) {
        if (WIFEXITED(status)) {
            printf("Child exited normally with code %d\n", WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("Child terminated by signal %d\n", WTERMSIG(status));
        }
    }
}

// Handler for SIGALRM (timeout)
void alarm_handler(int sig) {
    printf("Child did not finish in 5 seconds. Killing child...\n");
    kill(child_pid, SIGKILL);
}

int main() {
    signal(SIGCHLD, child_handler); // child death handler
    signal(SIGALRM, alarm_handler); // alarm handler

    child_pid = fork();

    if (child_pid < 0) {
        perror("fork");
        exit(1);
    }

    if (child_pid == 0) {
        // Child process: run a command (e.g., "sleep 10")
        execlp("sleep", "sleep", "10", NULL);
        perror("execlp failed");
        exit(1);
    } else {
        // Parent process
        alarm(5); // set 5-second timer
        pause();  // wait for signal (either SIGCHLD or SIGALRM)
        printf("Parent process exiting.\n");
    }

    return 0;
}
*/
