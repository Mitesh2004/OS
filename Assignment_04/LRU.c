#include <stdio.h>

int findLRU(int time[], int n) {
    int min = time[0], pos = 0;
    for (int i = 1; i < n; i++) {
        if (time[i] < min) {
            min = time[i];
            pos = i;
        }
    }
    return pos;
}

int main() {
    int pages[] = {12, 15, 12, 18, 6, 8, 11, 12, 19, 12, 6, 8, 12, 15, 19, 8};
    int frames[10], time[10], page_faults = 0, counter = 0, n;
    
    printf("Enter number of frames: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        frames[i] = -1;
        time[i] = 0;
    }

    for (int i = 0; i < 16; i++) {
        int found = 0;
        for (int j = 0; j < n; j++) {
            if (frames[j] == pages[i]) {
                counter++;
                time[j] = counter;
                found = 1;
                break;
            }
        }

        if (!found) {
            int lru = findLRU(time, n);
            frames[lru] = pages[i];
            counter++;
            time[lru] = counter;
            page_faults++;
        }

        printf("Accessing page %d: Frames: ", pages[i]);
        for (int j = 0; j < n; j++) {
            if (frames[j] == -1) printf("- ");
            else printf("%d ", frames[j]);
        }
        printf("\n");
    }
    
    printf("LRU: Total Page Faults = %d\n", page_faults);
    return 0;
}
