#include <stdio.h>

int main() {
    int p[] = {12, 15, 12, 18, 6, 8, 11, 12, 19, 12, 6, 8, 12, 15, 19, 8};
    int f[10], t[10], pf = 0, c = 0, n;

    printf("Enter number of frames: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) f[i] = t[i] = -1;

    for (int i = 0; i < 16; i++) {
        int found = 0;
        for (int j = 0; j < n; j++) {
            if (f[j] == p[i]) {
                t[j] = ++c;
                found = 1;
                break;
            }
        }

        if (!found) {
            int lru = 0;
            for (int j = 1; j < n; j++) 
                if (t[j] < t[lru]) lru = j;
            f[lru] = p[i];
            t[lru] = ++c;
            pf++;
        }

        printf("Page %d: ", p[i]);
        for (int j = 0; j < n; j++)  
            if (f[j] == -1) printf("- ");
            else printf("%d ", f[j]);
        printf("\n");
    }
    
    printf("Total Page Faults = %d\n", pf);
    return 0;
}
