#include <stdio.h>
#include <sys/resource.h>
#include <stdlib.h>

int main() {
    struct rlimit rl;

    // Current resource limits
    if(getrlimit(RLIMIT_NOFILE, &rl) == 0)
        printf("Max open files: soft=%lu, hard=%lu\n", rl.rlim_cur, rl.rlim_max);
    else perror("getrlimit");

    if(getrlimit(RLIMIT_AS, &rl) == 0)
        printf("Max memory: soft=%lu, hard=%lu\n", rl.rlim_cur, rl.rlim_max);
    else perror("getrlimit");

    // Update max open files
    if(getrlimit(RLIMIT_NOFILE, &rl) == 0) {
        rl.rlim_cur = 1024;
        if(setrlimit(RLIMIT_NOFILE, &rl) == 0) {
            if(getrlimit(RLIMIT_NOFILE, &rl) == 0)
                printf("\nUpdated Max open files: soft=%lu, hard=%lu\n", rl.rlim_cur, rl.rlim_max);
            else perror("getrlimit");
        } else perror("setrlimit");
    } else perror("getrlimit");

    return 0;
}
/*
m@Debian:~/Desktop/OS/MCS_Sem-1/golfed_code$ nano q22.c
m@Debian:~/Desktop/OS/MCS_Sem-1/golfed_code$ gcc q22.c
m@Debian:~/Desktop/OS/MCS_Sem-1/golfed_code$ ./a.out
Max open files: soft=1024, hard=1048576
Max memory: soft=18446744073709551615, hard=18446744073709551615

Updated Max open files: soft=1024, hard=1048576
*/



/*
#include <stdio.h>
#include <sys/resource.h>
#include <stdlib.h>

void print_limit(int resource, const char *name) {
    struct rlimit rl;
    if (getrlimit(resource, &rl) == -1) {
        perror("getrlimit");
        return;
    }
    printf("%s: Soft limit = %lu, Hard limit = %lu\n",
           name, rl.rlim_cur, rl.rlim_max);
}

int main() {
    printf("Current resource limits:\n");
    print_limit(RLIMIT_NOFILE, "Max open files");
    print_limit(RLIMIT_AS, "Max memory (address space)");

    // Example: set new soft limit for max open files
    struct rlimit new_rl;
    if (getrlimit(RLIMIT_NOFILE, &new_rl) == -1) {
        perror("getrlimit");
        exit(1);
    }

    new_rl.rlim_cur = 1024;  // new soft limit
    if (setrlimit(RLIMIT_NOFILE, &new_rl) == -1) {
        perror("setrlimit");
    } else {
        printf("\nUpdated resource limits:\n");
        print_limit(RLIMIT_NOFILE, "Max open files");
    }

    return 0;
}
*/
