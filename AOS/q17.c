#include <stdio.h>
#include <stdlib.h>

void bye1(){ puts("Goodbye from function 1!"); }
void bye2(){ puts("Goodbye from function 2!"); }

int main(){
    // Register functions to run at program exit
    atexit(bye1);
    atexit(bye2);
    puts("Main function is running...");
}

/*
m@Debian:~/Desktop/OS/MCS_Sem-1/golfed_code$ nano 17.c
m@Debian:~/Desktop/OS/MCS_Sem-1/golfed_code$ gcc 17.c
m@Debian:~/Desktop/OS/MCS_Sem-1/golfed_code$ ./a.out
Main function is running...
Goodbye from function 2!
Goodbye from function 1!
*/
