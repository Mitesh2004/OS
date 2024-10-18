#include <stdio.h>

int predict(int pages[], int frames[], int n, int index, int rs_size) {
    int res = -1, farthest = index;
    for (int i = 0; i < n; i++) {
        for (int j = index; j < rs_size; j++) {
            if (frames[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    res = i;
                }
                break;
            }
            if (j == rs_size - 1) return i;
        }
    }
    return (res == -1) ? 0 : res;
}

int main() {
    int pages[] = {12, 15, 12, 18, 6, 8, 11, 12, 19, 12, 6, 8, 12, 15, 19, 8};
    int frames[10], page_faults = 0, n;

    printf("Enter number of frames: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) frames[i] = -1;

    for (int i = 0; i < 16; i++) {
        int found = 0;
        for (int j = 0; j < n; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                break;
            }
        }
        if (!found) {
            if (i < n) {
                frames[i] = pages[i];
            } else {
                int j = predict(pages, frames, n, i, 16);
                frames[j] = pages[i];
            }
            page_faults++;
        }
        printf("Accessing page %d: Frames: ", pages[i]);
        for (int j = 0; j < n; j++) {
            if (frames[j] == -1) printf("- ");
            else printf("%d ", frames[j]);
        }
        printf("\n");
    }

    printf("Optimal: Total Page Faults = %d\n", page_faults);
    return 0;
}
