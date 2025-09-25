#include <stdio.h>

int main() {
    // Redirect stdout to a file
    freopen("output.txt", "w", stdout);

    // Anything printed now goes to output.txt instead of console
    printf("This text will be written to the file!\n");
    printf("Hello, file redirection works!\n");

    return 0;
}
/*
#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fp;

    // Open a file in write mode
    fp = freopen("output.txt", "w", stdout);
    if (fp == NULL) {
        perror("freopen failed");
        return 1;
    }

    // Now, all printf statements will go to output.txt
    printf("This text will be written to the file output.txt\n");
    printf("Redirection of standard output is successful!\n");

    // Optional: Close the file
    fclose(fp);

    return 0;
}
*/
