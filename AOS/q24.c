#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(){
    if(fork()==0){            // child
        printf("Child running...\n"); sleep(2); exit(42);
    }else{                    // parent
        int st; wait(&st);
        if(WIFEXITED(st)) printf("Child exited with code: %d\n", WEXITSTATUS(st));
        else printf("Child did not exit normally\n");
    }
}
/*
m@Debian:~/Desktop/OS/MCS_Sem-1/golfed_code$ nano q24.c
m@Debian:~/Desktop/OS/MCS_Sem-1/golfed_code$ gcc q24.c
m@Debian:~/Desktop/OS/MCS_Sem-1/golfed_code$ ./a.out
Child running...
Child exited with code: 42
*/
/*
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        // Child process
        printf("Child process running...\n");
        sleep(2); // simulate some work
        exit(42); // child exits with code 42
    } else {
        // Parent process
        int status;
        wait(&status); // wait for child to terminate

        if (WIFEXITED(status)) {
            printf("Child exited normally with exit code: %d\n", WEXITSTATUS(status));
        } else {
            printf("Child did not exit normally\n");
        }
    }

    return 0;
}
*/
