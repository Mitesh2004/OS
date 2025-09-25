#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(){
    int fd[2]; char buf[100]; pipe(fd);
    if(fork()==0){          // child
        close(fd[0]);
        char *msg[]={"Hello World","Hello SPPU","Linux is Funny"};
        for(int i=0;i<3;i++){
            write(fd[1], msg[i], 100); // write fixed 100 bytes
        }
        close(fd[1]);
    }else{                  // parent
        close(fd[1]);
        for(int i=0;i<3;i++){
            read(fd[0], buf, 100);
            printf("Parent received: %s\n", buf);
        }
        close(fd[0]);
    }
}
/*
m@Debian:~/Desktop/OS/MCS_Sem-1/golfed_code$ nano q21.c
m@Debian:~/Desktop/OS/MCS_Sem-1/golfed_code$ gcc q21.c
m@Debian:~/Desktop/OS/MCS_Sem-1/golfed_code$ ./a.out
Parent received: Hello World
Parent received: Hello SPPU
Parent received: Linux is Funny
*/

/*
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd[2];
    char buf[100];

    if (pipe(fd) == -1) {
        perror("pipe");
        return 1;
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    }
    else if (pid == 0) {
        // Child process: write messages
        close(fd[0]); // close read end

        char *messages[] = {
            "Hello World",
            "Hello SPPU",
            "Linux is Funny"
        };

        for (int i = 0; i < 3; i++)
            write(fd[1], messages[i], strlen(messages[i]) + 1); // include '\0'

        close(fd[1]);
    }
    else {
        // Parent process: read messages
        close(fd[1]); // close write end

        for (int i = 0; i < 3; i++) {
            int n = read(fd[0], buf, sizeof(buf));
            if (n > 0)
                printf("Parent received: %s\n", buf);
        }

        close(fd[0]);
    }

    return 0;
}
*/
