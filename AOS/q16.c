#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(){
    int p2c[2],c2p[2]; char buf[100];
    if(pipe(p2c)<0||pipe(c2p)<0) return perror("pipe"),1;
    if(fork()){ // parent
        close(p2c[0]); close(c2p[1]);
        write(p2c[1],"Hello Child!",13);
        read(c2p[0],buf,sizeof(buf));
        printf("Parent received: %s\n",buf);
    }else{ // child
        close(p2c[1]); close(c2p[0]);
        read(p2c[0],buf,sizeof(buf));
        printf("Child received: %s\n",buf);
        write(c2p[1],"Hi Parent!",11);
    }
}
/*
m@Debian:~/Desktop/OS/MCS_Sem-1/golfed_code$ nano q16.c
m@Debian:~/Desktop/OS/MCS_Sem-1/golfed_code$ gcc q16.c
m@Debian:~/Desktop/OS/MCS_Sem-1/golfed_code$ ./a.out
Child received: Hello Child!
Parent received: Hi Parent!
*/

/*
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    int p2c[2], c2p[2]; // parent-to-child, child-to-parent
    char buf[100];

    if (pipe(p2c) == -1 || pipe(c2p) == -1) {
        perror("pipe");
        return 1;
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    }
    else if (pid > 0) {   // Parent process
        close(p2c[0]); // close read end of p2c
        close(c2p[1]); // close write end of c2p

        char msg[] = "Hello Child!";
        write(p2c[1], msg, strlen(msg) + 1);

        read(c2p[0], buf, sizeof(buf));
        printf("Parent received: %s\n", buf);

        close(p2c[1]);
        close(c2p[0]);
    }
    else {      // Child process
        close(p2c[1]); // close write end of p2c
        close(c2p[0]); // close read end of c2p

        read(p2c[0], buf, sizeof(buf));
        printf("Child received: %s\n", buf);

        char reply[] = "Hi Parent!";
        write(c2p[1], reply, strlen(reply) + 1);

        close(p2c[0]);
        close(c2p[1]);
    }

    return 0;
}
*/
