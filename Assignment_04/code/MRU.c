#include <stdio.h>

int main() {
    int p[] = {12, 15, 12, 18, 6, 8, 11, 12, 19, 12, 6, 8, 12, 15, 19, 8};
    int n, i, j, f[10], pf = 0, mr = 0 ,found = 0;

    printf("Enter number of frames: ");
    scanf("%d", &n);

    for ( i = 0; i < n; i++) f[i] = -1;

    for ( i = 0; i < 16; i++) {
         found = 0;
        for ( j = 0; j < n; j++) {
            if (f[j] == p[i]) {
                found = 1;
                mr = j;
                break;
            }
        }
        if (!found) {
            f[mr] = p[i];
            mr = (mr + 1) % n;
            pf++;
        }
        printf("Accessing page %d: Frames: ", p[i]);
        for ( j = 0; j < n; j++) {
            if (f[j] == -1) printf("- ");
            else printf("%d ", f[j]);
        }
        printf("\n");
    }

    printf("MRU: Total Page Faults = %d\n", pf);
    return 0;
}

