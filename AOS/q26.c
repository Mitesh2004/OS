#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void h(int s){
    if(s==SIGHUP) puts("Child got SIGHUP");
    else if(s==SIGINT) puts("Child got SIGINT");
    else { puts("Child got SIGQUIT. My Papa killed me!"); exit(0); }
}

int main(){
    pid_t pid=fork();
    if(pid<0) return perror("fork"),1;

    if(!pid){ // child
        signal(SIGHUP,h); signal(SIGINT,h); signal(SIGQUIT,h);
        while(1) pause();
    } else {  // parent
        sleep(1);
        for(int i=0;i<5;i++){ kill(pid,i%2?SIGINT:SIGHUP); sleep(3); }
        kill(pid,SIGQUIT);
        wait(NULL);
        puts("Parent: Child terminated.");
    }
}
/*
m@Debian:~/Desktop/OS/MCS_Sem-1/golfed_code$ nano q26.c
m@Debian:~/Desktop/OS/MCS_Sem-1/golfed_code$ gcc q26.c
m@Debian:~/Desktop/OS/MCS_Sem-1/golfed_code$ ./a.out
Child got SIGHUP
Child got SIGINT
Child got SIGHUP
Child got SIGINT
Child got SIGHUP
Child got SIGQUIT. My Papa killed me!
Parent: Child terminated.
*/
/*
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void handler(int sig){
    if(sig==SIGHUP)  printf("Child got SIGHUP\n");
    if(sig==SIGINT)  printf("Child got SIGINT\n");
    if(sig==SIGQUIT){ printf("Child got SIGQUIT. My Papa killed me!\n"); exit(0); }
    fflush(stdout);
}

int main(){
    pid_t pid=fork();
    if(pid<0){ perror("fork"); exit(1); }

    if(pid==0){   // child
        signal(SIGHUP,handler);
        signal(SIGINT,handler);
        signal(SIGQUIT,handler);
        while(1) pause();
    }
    else{         // parent
        sleep(1);
        for(int i=0;i<5;i++){
            kill(pid,(i%2==0)?SIGHUP:SIGINT);
            sleep(3);
        }
        kill(pid,SIGQUIT);
        wait(NULL);
        printf("Parent: Child has terminated.\n");
    }
}
*/
/*
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void sighup_handler(int sig) {
    printf("Child received SIGHUP\n");
}

void sigint_handler(int sig) {
    printf("Child received SIGINT\n");
}

void sigquit_handler(int sig) {
    printf("Child received SIGQUIT. My Papa has Killed me!!!\n");
    exit(0);
}

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) {
        // Child process
        signal(SIGHUP, sighup_handler);
        signal(SIGINT, sigint_handler);
        signal(SIGQUIT, sigquit_handler);

        while (1) {
            pause(); // wait for signals
        }
    } else {
        // Parent process
        sleep(1); // give child time to set handlers

        for (int i = 0; i < 5; i++) {
            if (i % 2 == 0) {
                kill(pid, SIGHUP);
            } else {
                kill(pid, SIGINT);
            }
            sleep(3);
        }

        // After ~15 seconds, send SIGQUIT
        kill(pid, SIGQUIT);

        wait(NULL); // wait for child to terminate
        printf("Parent: Child has terminated.\n");
    }

    return 0;
}
*/
