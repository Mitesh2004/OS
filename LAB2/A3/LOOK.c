#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, head, i, j, temp, total_seek_time = 0, direction, disk_size;

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

    // Sort the request queue
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (request[i] > request[j]) {
                temp = request[i];
                request[i] = request[j];
                request[j] = temp;
            }
        }
    }

    // Find the start index
    int start = 0;
    while (start < n && request[start] < head) start++;

    printf("\nLOOK Seek sequence: %d", head);
    int current_head = head;

    if (direction == 1) {  // Move right first
        for (i = start; i < n; i++) {
            total_seek_time += abs(request[i] - current_head);
            current_head = request[i];
            printf(" -> %d", current_head);
        }
        for (i = start - 1; i >= 0; i--) {
            total_seek_time += abs(request[i] - current_head);
            current_head = request[i];
            printf(" -> %d", current_head);
        }
    } else {  // Move left first
        for (i = start - 1; i >= 0; i--) {
            total_seek_time += abs(request[i] - current_head);
            current_head = request[i];
            printf(" -> %d", current_head);
        }
        for (i = start; i < n; i++) {
            total_seek_time += abs(request[i] - current_head);
            current_head = request[i];
            printf(" -> %d", current_head);
        }
    }

    printf("\nTotal seek time: %d\n", total_seek_time);
    return 0;
}

