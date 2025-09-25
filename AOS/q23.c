// simllar like q19
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    int fd[2]; pipe(fd);

    if(fork()==0){          // child 1: ls -l
        close(fd[0]); dup2(fd[1],1); close(fd[1]);
        execlp("ls","ls","-l",NULL); perror("execlp ls"); exit(1);
    }

    if(fork()==0){          // child 2: wc -l
        close(fd[1]); dup2(fd[0],0); close(fd[0]);
        execlp("sh", "sh", "-c", "echo -n 'totalLine: ' && wc -l", NULL);
        perror("execlp wc"); exit(1);
       // execlp("wc","wc","-l",NULL); perror("execlp wc"); exit(1);
    }

    close(fd[1]); close(fd[0]); // parent closes both ends
    wait(NULL); wait(NULL);     // wait for children
}
/*
m@Debian:~/Desktop/OS/MCS_Sem-1/golfed_code$ nano q23.c
m@Debian:~/Desktop/OS/MCS_Sem-1/golfed_code$ gcc q23.c
m@Debian:~/Desktop/OS/MCS_Sem-1/golfed_code$ ./a.out
totalLine: 39
*/


/*
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int fd[2];
    if (pipe(fd) == -1) {
        perror("pipe");
        exit(1);
    }

    pid_t pid1 = fork();
    if (pid1 < 0) { perror("fork"); exit(1); }

    if (pid1 == 0) {
        // First child: executes ls -l
        close(fd[0]);              // Close read end
        dup2(fd[1], STDOUT_FILENO); // Redirect stdout to pipe
        close(fd[1]);
        execlp("ls", "ls", "-l", NULL);
        perror("execlp ls"); exit(1);
    }

    pid_t pid2 = fork();
    if (pid2 < 0) { perror("fork"); exit(1); }

    if (pid2 == 0) {
        // Second child: executes wc -l
        close(fd[1]);              // Close write end
        dup2(fd[0], STDIN_FILENO); // Redirect stdin from pipe
        close(fd[0]);
        execlp("wc", "wc", "-l", NULL);
        perror("execlp wc"); exit(1);
    }

    // Parent process
    close(fd[0]);
    close(fd[1]);

    // Wait for both children
    wait(NULL);
    wait(NULL);

    return 0;
}
*/
