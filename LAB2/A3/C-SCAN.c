#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, head, disk_size, direction, i, j, temp, total_seek_time = 0;

    printf("Enter number of requests: ");
    scanf("%d", &n);
    int request[n];

    printf("Enter request queue: ");
    for (i = 0; i < n; i++) scanf("%d", &request[i]);

    printf("Enter disk size: ");
    scanf("%d", &disk_size);
    printf("Enter initial head position: ");
    scanf("%d", &head);
    printf("Enter direction (1 for right, 0 for left): ");
    scanf("%d", &direction);

    // Sorting the request queue
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (request[i] > request[j]) {
                temp = request[i];
                request[i] = request[j];
                request[j] = temp;
            }
        }
    }

    // Find starting index
    int start = 0;
    while (start < n && request[start] < head) start++;

    printf("Seek sequence: %d", head);

    if (direction == 1) {  // Moving right first
        for (i = start; i < n; i++) {
            total_seek_time += abs(request[i] - head);
            head = request[i];
            printf(" -> %d", head);
        }

        // Move to the end of disk
        if (head != disk_size - 1) {
            printf(" -> %d", disk_size - 1);
            total_seek_time += abs(disk_size - 1 - head);
        }

        // Jump to the start (No seek time added)
        head = 0;
        printf(" -> 0");

        for (i = 0; i < start; i++) {
            total_seek_time += abs(request[i] - head);
            head = request[i];
            printf(" -> %d", head);
        }
    } else {  // Moving left first
        for (i = start - 1; i >= 0; i--) {
            total_seek_time += abs(request[i] - head);
            head = request[i];
            printf(" -> %d", head);
        }

        // Move to the start of disk
        if (head != 0) {
            printf(" -> 0");
            total_seek_time += abs(head);
        }

        // Jump to the end (No seek time added)
        head = disk_size - 1;
        printf(" -> %d", disk_size - 1);

        for (i = n - 1; i >= start; i--) {
            total_seek_time += abs(request[i] - head);
            head = request[i];
            printf(" -> %d", head);
        }
    }

    printf("\nTotal seek time: %d\n", total_seek_time);
    return 0;
}
