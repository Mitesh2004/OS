#include <stdio.h>

int main() {
    int p[] = {12, 15, 12, 18, 6, 8, 11, 12, 19, 12, 6, 8, 12, 15, 19, 8};
    int f[10], fq[10], pf = 0, n;

    printf("Enter number of frames: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) f[i] = -1, fq[i] = 0;

    for (int i = 0; i < 16; i++) {
        int found = 0;
        for (int j = 0; j < n; j++) {
            if (f[j] == p[i]) {
                fq[j]++;
                found = 1;
                break;
            }
        }
        if (!found) {
            int pos = 0, mfq = fq[0];
            for (int j = 1; j < n; j++) {
                if (f[j] == -1 || fq[j] < mfq) {
                    mfq = fq[j];
                    pos = j;
                }
            }
            f[pos] = p[i];
            fq[pos] = 1;
            pf++;
        }
        printf("Accessing page %d: Frames: ", p[i]);
        for (int j = 0; j < n; j++) {
            if (f[j] == -1) printf("- ");
            else printf("%d ", f[j]);
        }
        printf("\n");
    }
    printf("LFU: Total Page Faults = %d\n", pf);
    return 0;
}

