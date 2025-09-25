#include <stdio.h>
#include <setjmp.h>
int main(){
    jmp_buf env; int g=1;
    int a=1; register int r=1; static int s=1; volatile int v=1;

    printf("\na=%d, r=%d, s=%d, g=%d, v=%d\n",a,r,s,g,v);
    a++; r++; s++; g++; v++;

    if(!setjmp(env)){
        puts("Calling longjmp...");
        longjmp(env,1);
    } else {
        printf("After longjmp: a=%d, r=%d, s=%d, g=%d, v=%d\n",a,r,s,g,v);
    }
}
/*
m@Debian:~/Desktop/OS/MCS_Sem-1/golfed_code$ nano q18.c
m@Debian:~/Desktop/OS/MCS_Sem-1/golfed_code$ gcc q18.c
m@Debian:~/Desktop/OS/MCS_Sem-1/golfed_code$ ./a.out

a=1, r=1, s=1, g=1, v=1
Calling longjmp...
After longjmp: a=2, r=2, s=2, g=2, v=2
*/
/*
#include <stdio.h>
#include <setjmp.h>
jmp_buf env; int g=1;

void test(){
    int a=1; register int r=1; static int s=1; volatile int v=1;
    printf("\na=%d, r=%d, s=%d, g=%d, v=%d\n",a,r,s,g,v);
    a++; r++; s++; g++; v++;
    if(!setjmp(env)){ puts("Calling longjmp..."); longjmp(env,1); }
    else printf("After longjmp: a=%d, r=%d, s=%d, g=%d, v=%d\n",a,r,s,g,v);
}

int main(){ test(); }
*/
/*
#include <stdio.h>
#include <setjmp.h>

jmp_buf env;

// Global variable (retains value always)
int g = 1;

void test() {
    // Automatic variable (re-initialized every call)
    int a = 1;

    // Register variable (similar to auto, but hint for CPU register use)
    register int r = 1;

    // Static variable (retains value between calls)
    static int s = 1;

    // Volatile variable (value is not optimized away, always read fresh)
    volatile int v = 1;

    printf("\nInside test():\n");
    printf("auto a=%d, register r=%d, static s=%d, global g=%d, volatile v=%d\n", a, r, s, g, v);

    a++; r++; s++; g++; v++;

    // Save state first time, then jump back second time
    if (setjmp(env) == 0) {
        printf("Calling longjmp()...\n");
        longjmp(env, 1);
    } else {
        printf("After longjmp() in test():\n");
        printf("auto a=%d, register r=%d, static s=%d, global g=%d, volatile v=%d\n", a, r, s, g, v);
    }
}

int main() {
    test();
    return 0;
}
*/
