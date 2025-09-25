/*
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main() {
    int fd[2]; 
    pipe(fd);

    // Block SIGINT and SIGQUIT
    sigset_t block;
    sigemptyset(&block);
    sigaddset(&block, SIGINT);
    sigaddset(&block, SIGQUIT);
    sigprocmask(SIG_BLOCK, &block, NULL);

    if (fork() == 0) { // child: ls -l
        close(fd[0]);
        dup2(fd[1], 1); // redirect stdout to pipe
        close(fd[1]);
        execlp("ls", "ls", "-l", NULL);
        perror("execlp"); 
        exit(1);
    } else { // parent: wc -l
        close(fd[1]);
        int lines = 0;
        char c;
        while (read(fd[0], &c, 1) > 0) {
            if (c == '\n') lines++;
        }
        close(fd[0]);
        printf("Total lines: %d\n", lines);
    }
}
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main(){
    int fd[2]; pipe(fd);

    // Block SIGINT and SIGQUIT
    sigset_t b; sigemptyset(&b); sigaddset(&b,SIGINT); sigaddset(&b,SIGQUIT);
    sigprocmask(SIG_BLOCK,&b,NULL);

    if(!fork()){          // child: ls -l
        close(fd[0]); dup2(fd[1],1); close(fd[1]);
        execlp("ls","ls","-l",NULL); perror("execlp ls"); exit(1);
    }else{                // parent: read & count lines
        close(fd[1]);
        char c; int cnt=0;
        while(read(fd[0],&c,1)>0){ putchar(c); if(c=='\n') cnt++; }
        printf("Total lines: %d\n",cnt);
    }
}
/*
m@Debian:~/Desktop/OS/MCS_Sem-1/golfed_code$ nano q30.c
m@Debian:~/Desktop/OS/MCS_Sem-1/golfed_code$ gcc q30.c
m@Debian:~/Desktop/OS/MCS_Sem-1/golfed_code$ ./a.out
total 816
-rwxr-xr-x 1 m m  16576 Sep 25 13:43 a.out
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
-rw-r--r-- 1 m m   4313 Sep 25 00:13 q19.c
-rw-r--r-- 1 m m    621 Sep 19 21:23 q1.c
-rw-r--r-- 1 m m   2106 Sep 25 00:38 q20.c
-rw-r--r-- 1 m m   1811 Sep 25 00:45 q21.c
-rw-r--r-- 1 m m   2142 Sep 25 00:50 q22.c
-rw-r--r-- 1 m m   1916 Sep 25 01:01 q23.c
-rw-r--r-- 1 m m   1325 Sep 25 01:05 q24.c
-rw-r--r-- 1 m m   1219 Sep 25 01:11 q25.c
-rw-r--r-- 1 m m   3017 Sep 25 13:11 q26.c
-rw-r--r-- 1 m m   1986 Sep 25 13:22 q27.c
-rw-r--r-- 1 m m   2129 Sep 25 13:25 q28.c
-rw-r--r-- 1 m m   2301 Sep 25 13:29 q29.c
-rw-r--r-- 1 m m    565 Sep 19 21:26 q2.c
-rw-r--r-- 1 m m   2333 Sep 25 13:43 q30.c
-rw-r--r-- 1 m m    957 Sep 19 21:27 q3.c
-rw-r--r-- 1 m m   1207 Sep 19 21:30 q4.c
-rw-r--r-- 1 m m    522 Sep 19 21:32 q5.c
-rw-r--r-- 1 m m    565 Sep 19 21:46 q6.c
-rw-r--r-- 1 m m    638 Sep 19 21:47 q7.c
-rw-r--r-- 1 m m   2407 Sep 24 00:00 q8.c
-rw-r--r-- 1 m m   2377 Sep 24 00:08 q9.c
drwxr-xr-x 2 m m   4096 Sep 24 01:05 strawberry
-rw-r--r-- 1 m m   2553 Sep 23 23:50 tPwME.txt
Total lines: 46
*/
/*
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main() {
    int fd[2];
    pipe(fd);

    // Block Ctrl-C (SIGINT) and Ctrl-\ (SIGQUIT)
    sigset_t block_set;
    sigemptyset(&block_set);
    sigaddset(&block_set, SIGINT);
    sigaddset(&block_set, SIGQUIT);
    if (sigprocmask(SIG_BLOCK, &block_set, NULL) < 0) {
        perror("sigprocmask");
        exit(1);
    }

    if (fork() == 0) { // child: ls -l
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
        execlp("ls", "ls", "-l", NULL);
        perror("execlp ls");
        exit(1);
    } else { // parent: read & count lines
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
*/
