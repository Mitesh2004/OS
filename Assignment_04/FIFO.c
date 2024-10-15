#include <stdio.h>
int main() {
    int pages[] = {12, 15, 12, 18, 6, 8, 11, 12, 19, 12, 6, 8, 12, 15, 19, 8};
    int n, frames[10], page_faults = 0, next = 0;

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
            frames[next] = pages[i];
            next = (next + 1) % n;
            page_faults++;
        }
        printf("Accessing page %d: Frames: ", pages[i]);
        for (int j = 0; j < n; j++) {
            if (frames[j] == -1) printf("- ");
            else printf("%d ", frames[j]);
        }
        printf("\n");
    }
    printf("FIFO: Total Page Faults = %d\n", page_faults);
    return 0;
}
