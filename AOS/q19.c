#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main() {
    int fd[2];
    pipe(fd);
    if (fork() == 0) {          // child: ls -l
        close(fd[0]);
        dup2(fd[1], 1);
        execlp("ls", "ls", "-l", NULL);
    } else {                    // parent: print & count
        close(fd[1]);
        char c;
        int count = 0;
        while (read(fd[0], &c, 1) > 0) {
            putchar(c);
            if (c == '\n') count++;
        }
        printf("Total lines: %d\n", count);
    }
    return 0;
}
/*
m@Debian:~/Desktop/OS/MCS_Sem-1/golfed_code$ nano q19.c
m@Debian:~/Desktop/OS/MCS_Sem-1/golfed_code$ gcc q19.c
m@Debian:~/Desktop/OS/MCS_Sem-1/golfed_code$ ./a.out
total 764
-rwxr-xr-x 1 m m  16312 Sep 25 00:12 a.out
drwxr-xr-x 2 m m   4096 Sep 24 01:03 apple
drwxr-xr-x 2 m m   4096 Sep 24 01:04 blueberry
-rw-r--r-- 1 m m 343356 Sep 24 00:18 CS504-MJP-AOS-Slips.pdf
-rw-r--r-- 1 m m      6 Sep 18 13:43 file1.txt
-rw-r--r-- 1 m m      6 Sep 18 13:43 file2.txt
-rw-r--r-- 1 m m  10010 Sep 19 21:22 file_with_hole.txt
drwxr-xr-x 2 m m   4096 Sep 24 01:08 mango
-rw-r--r-- 1 m m    650 Sep 19 21:21 note
drwxr-xr-x 2 m m   4096 Sep 24 01:04 orange
-rw-r--r-- 1 m m 288352 Sep 18 13:31 os_lab-book.pdf
-rw-r--r-- 1 m m     31 Sep 24 16:10 output1.txt
-rw-r--r-- 1 m m     70 Sep 24 00:25 output.txt
-rw-r--r-- 1 m m   1732 Sep 24 00:23 q10.c
-rw-r--r-- 1 m m    778 Sep 24 00:25 q11.c
-rw-r--r-- 1 m m   1605 Sep 24 01:08 q12.c
-rw-r--r-- 1 m m    932 Sep 24 16:11 q13.c
-rw-r--r-- 1 m m   2017 Sep 25 00:12 q14.c
-rw-r--r-- 1 m m   1361 Sep 24 23:42 q15.c
-rw-r--r-- 1 m m   1854 Sep 24 23:45 q16.c
-rw-r--r-- 1 m m    526 Sep 24 23:48 q17.c
-rw-r--r-- 1 m m   2064 Sep 24 23:54 q18.c
-rw-r--r-- 1 m m   2592 Sep 25 00:12 q19.c
-rw-r--r-- 1 m m    621 Sep 19 21:23 q1.c
-rw-r--r-- 1 m m    565 Sep 19 21:26 q2.c
-rw-r--r-- 1 m m    957 Sep 19 21:27 q3.c
-rw-r--r-- 1 m m   1207 Sep 19 21:30 q4.c
-rw-r--r-- 1 m m    522 Sep 19 21:32 q5.c
-rw-r--r-- 1 m m    565 Sep 19 21:46 q6.c
-rw-r--r-- 1 m m    638 Sep 19 21:47 q7.c
-rw-r--r-- 1 m m   2407 Sep 24 00:00 q8.c
-rw-r--r-- 1 m m   2377 Sep 24 00:08 q9.c
drwxr-xr-x 2 m m   4096 Sep 24 01:05 strawberry
-rw-r--r-- 1 m m   2553 Sep 23 23:50 tPwME.txt
Total lines: 35
*/

/*
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
    int fd[2]; pid_t pid;
    if(pipe(fd)<0) return perror("pipe"),1;
    if((pid=fork())<0) return perror("fork"),1;

    if(pid==0){         // child: ls -l
        close(fd[0]); dup2(fd[1],1); close(fd[1]);
        execlp("ls","ls","-l",NULL); perror("execlp ls"); exit(1);
    }else{              // parent: wc -l
        close(fd[1]); dup2(fd[0],0); close(fd[0]);
        execlp("wc","wc","-l",NULL); perror("execlp wc"); exit(1);
    }
}
*/

/*
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
    int fd[2]; pid_t pid;
    if(pipe(fd)<0) return perror("pipe"),1;
    if((pid=fork())<0) return perror("fork"),1;

    if(pid==0){ // child: ls -l
        printf("Child: ls -l output :\n"); fflush(stdout); // label
        close(fd[0]); dup2(fd[1],1); close(fd[1]);
        execlp("ls","ls","-l",NULL); perror("execlp ls"); exit(1);
    }else{ // parent: wc -l
        printf("Parent: counting lines from child ls output :\n"); fflush(stdout);
        close(fd[1]); dup2(fd[0],0); close(fd[0]);
        execlp("wc","wc","-l",NULL); perror("execlp wc"); exit(1);
    }
}
*/
/*
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int fd[2];
    pid_t pid;

    if (pipe(fd) == -1) {
        perror("pipe");
        exit(1);
    }

    pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) {
        // Child process: run "ls -l"
        close(fd[0]);               // close unused read end
        dup2(fd[1], STDOUT_FILENO); // redirect stdout to pipe
        close(fd[1]);

        execlp("ls", "ls", "-l", NULL);
        perror("execlp ls"); // exec failed
        exit(1);
    } else {
        // Parent process: run "wc -l"
        close(fd[1]);               // close unused write end
        dup2(fd[0], STDIN_FILENO);  // redirect stdin from pipe
        close(fd[0]);

        execlp("wc", "wc", "-l", NULL);
        perror("execlp wc");
        exit(1);
    }

    return 0;
}
*/
