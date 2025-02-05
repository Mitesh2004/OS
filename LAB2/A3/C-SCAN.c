#include <stdio.h>
#include <stdlib.h>

int main() {
    int i, j, n, head, total_seek_time = 0, disk_size, direction;

    // Input number of disk requests
    printf("Enter number of disk requests: ");
    scanf("%d", &n);
    int request[n];

    // Input disk request queue
    printf("Enter disk request queue: ");
    for (i = 0; i < n; i++) {
        scanf("%d", &request[i]);
    }

    // Input initial head position
    printf("Enter initial head position: ");
    scanf("%d", &head);

    // Input disk size (max cylinder number)
    printf("Enter disk size: ");
    scanf("%d", &disk_size);

    // Input direction (0 = left/down, 1 = right/up)
    printf("Enter direction (0 for left, 1 for right): ");
    scanf("%d", &direction);

    // Sorting requests
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (request[i] > request[j]) {
                int temp = request[i];
                request[i] = request[j];
                request[j] = temp;
            }
        }
    }

    // Finding head position in sorted request array
    int pos = 0;
    while (pos < n && request[pos] < head) {
        pos++;
    }

    // Display seek sequence
    printf("SEEK SEQUENCE: %d", head);

    if (direction == 1) { // Moving right (up)
        for (i = pos; i < n; i++) {
            total_seek_time += abs(request[i] - head);
            head = request[i];
            printf(" -> %d", head);
        }

        // Move to end of disk
        if (head != disk_size - 1) {
            total_seek_time += abs(disk_size - 1 - head);
            head = disk_size - 1;
            printf(" -> %d", head);
        }

        // Jump to start of disk (DO NOT COUNT THIS AS SEEK TIME)
        head = 0;
        printf(" -> %d", head);

        // Process remaining requests on the left
        for (i = 0; i < pos; i++) {
            total_seek_time += abs(request[i] - head);
            head = request[i];
            printf(" -> %d", head);
        }
    } else { // Moving left (down)
        for (i = pos - 1; i >= 0; i--) {
            total_seek_time += abs(request[i] - head);
            head = request[i];
            printf(" -> %d", head);
        }

        // Move to start of disk
        if (head != 0) {
            total_seek_time += abs(head - 0);
            head = 0;
            printf(" -> %d", head);
        }

        // Jump to end of disk (DO NOT COUNT THIS AS SEEK TIME)
        head = disk_size - 1;
        printf(" -> %d", head);

        // Process remaining requests on the right
        for (i = n - 1; i >= pos; i--) {
            total_seek_time += abs(request[i] - head);
            head = request[i];
            printf(" -> %d", head);
        }
    }

    // Output total and average seek time
    printf("\n\nTotal seek time: %d\n", total_seek_time);
    printf("Average seek time: %.2f\n", (float)total_seek_time / n);

    return 0;
}

