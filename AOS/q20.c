#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <unistd.h>

int main() {
    int n;
    printf("Enter number of child processes: ");
    fflush(stdout);
    scanf("%d", &n);

    struct rusage u;
    double tu=0, ts=0;

    for(int i=0;i<n;i++)
        if(fork()==0){ for(volatile long j=0;j<100000000;j++); exit(0); }

    for(int i=0;i<n;i++){
        wait3(NULL,0,&u);
        tu += u.ru_utime.tv_sec + u.ru_utime.tv_usec/1e6;
        ts += u.ru_stime.tv_sec + u.ru_stime.tv_usec/1e6;
    }

    printf("User time: %.6f sec\nSystem time: %.6f sec\n", tu, ts);
}
/*
m@Debian:~/Desktop/OS/MCS_Sem-1/golfed_code$ nano q20.c
m@Debian:~/Desktop/OS/MCS_Sem-1/golfed_code$ nano q20.c
m@Debian:~/Desktop/OS/MCS_Sem-1/golfed_code$ gcc q20.c
m@Debian:~/Desktop/OS/MCS_Sem-1/golfed_code$ ./a.out
Enter number of child processes: 22
User time: 4.540495 sec
System time: 0.008021 sec
m@Debian:~/Desktop/OS/MCS_Sem-1/golfed_code$ ./a.out
Enter number of child processes: 123
User time: 25.437346 sec
System time: 0.003622 sec
*/

/*
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>

int main() {
    int n;
    printf("Enter number of child processes: ");
    scanf("%d", &n);

    struct rusage usage;
    long total_utime_sec = 0, total_stime_sec = 0;

    for (int i = 0; i < n; i++) {
        pid_t pid = fork();
        if (pid < 0) {
            perror("fork");
            exit(1);
        }
        if (pid == 0) {
            // Child process: do some work
            for (volatile long j = 0; j < 100000000; j++); // busy loop
            exit(0);
        }
    }

    // Parent waits for all children
    for (int i = 0; i < n; i++) {
        wait3(NULL, 0, &usage);
        total_utime_sec += usage.ru_utime.tv_sec;
        total_stime_sec += usage.ru_stime.tv_sec;
    }

    printf("Total cumulative time of children:\n");
    printf("User time: %ld sec\n", total_utime_sec);
    printf("System time: %ld sec\n", total_stime_sec);

    return 0;
}
*/
