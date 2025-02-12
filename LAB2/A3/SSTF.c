#include <stdio.h>
#include <stdlib.h>
#include <limits.h>  // Use INT_MAX instead of MIN

int main() {
    int i, j;
    int n, head, total_seek_time = 0, temp, min_seek, min_idx;

    // Input: Number of disk requests
    printf("Enter no. of disk requests: ");
    scanf("%d", &n);
    int request[n], visited[n];

    // Input: Disk request queue
    printf("Enter disk request queue: ");
    for (i = 0; i < n; i++) {
        scanf("%d", &request[i]);
        visited[i] = 0; // Mark all as unvisited
    }

    // Input: Initial head position
    printf("Enter initial head: ");
    scanf("%d", &head);

    // Display seek sequence
    printf("SEEK SEQUENCE: %d", head);
    for (i = 0; i < n; i++) {
        // Find closest unvisited request
        min_seek = INT_MAX;
        min_idx = -1; // Initialize properly

        for (j = 0; j < n; j++) {
            if (!visited[j]) { // If request is unvisited
                temp = abs(request[j] - head);
                if (temp < min_seek) {
                    min_seek = temp;
                    min_idx = j;
                }
            }
        }

        // Move head to the closest request
        total_seek_time += min_seek;
        head = request[min_idx];
        visited[min_idx] = 1; // Mark as visited
        printf(" -> %d", head);
    }

    // Output: Total and Average Seek Time
    printf("\n\nTotal seek time: %d\n", total_seek_time);
    printf("Average seek time: %.2f\n", (float)total_seek_time / n);

    return 0;
}


