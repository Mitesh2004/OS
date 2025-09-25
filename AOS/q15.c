#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(){
    int fd[2]; char buf[100]; 
    if(pipe(fd)<0) return perror("pipe"),1;
    if(fork()){ // parent
        close(fd[0]);
        write(fd[1],"Hello from parent!",18);
        close(fd[1]);
    }else{      // child
        close(fd[1]);
        read(fd[0],buf,sizeof(buf));
        printf("Child read: %s\n",buf);
        close(fd[0]);
    }
}
/*
m@Debian:~/Desktop/OS/MCS_Sem-1/golfed_code$ nano q15.c
m@Debian:~/Desktop/OS/MCS_Sem-1/golfed_code$ gcc q15.c
m@Debian:~/Desktop/OS/MCS_Sem-1/golfed_code$ ./a.out
Child read: Hello from parent!
*/

/*
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd[2];
    char write_msg[] = "Hello from parent!";
    char read_buf[100];

    if (pipe(fd) == -1) {
        perror("pipe");
        return 1;
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    }
    else if (pid > 0) {
        // Parent process
        close(fd[0]); // close read end
        write(fd[1], write_msg, strlen(write_msg) + 1);
        close(fd[1]); // finished writing
    }
    else {
        // Child process
        close(fd[1]); // close write end
        read(fd[0], read_buf, sizeof(read_buf));
        printf("Child read: %s\n", read_buf);
        close(fd[0]);
    }

    return 0;
}
*/
