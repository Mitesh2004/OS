#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
    int fd=open("output1.txt",O_WRONLY|O_CREAT|O_TRUNC,0644);
    if(fd<0) return perror("open"),1;
    if(dup2(fd,1)<0) return perror("dup2"),1;
    close(fd);
    printf("Hello! This goes to output1.txt\n");
}


/*
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    // Open (or create) output.txt with write permissions
    int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    // Redirect stdout (fd = 1) to this file
    if (dup2(fd, STDOUT_FILENO) < 0) {
        perror("dup2");
        return 1;
    }
    close(fd);  // no longer need original fd

    // Now printf goes into output.txt instead of terminal
    printf("Hello! This is written via dup2 redirection.\n");
    printf("All stdout is now captured in output.txt\n");

    return 0;
}
*/
