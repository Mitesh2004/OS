#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// FCFS (First Come First Serve)
void fcfs(int request[], int n, int head) {
	int total_seek_time = 0;
	printf("\nFCFS SEEK SEQUENCE: %d", head);

	for (int i = 0; i < n; i++) {
		total_seek_time += abs(request[i] - head);
		head = request[i];
		printf(" -> %d", head);
	}

	printf("\nTotal Seek Time: %d", total_seek_time);
	printf("\nAverage Seek Time: %.2f\n", (float)total_seek_time / n);
}

// SSTF (Shortest Seek Time First)
void sstf(int request[], int n, int head) {
	int total_seek_time = 0, visited[MAX] = {0};

	printf("\nSSTF SEEK SEQUENCE: %d", head);
	for (int i = 0; i < n; i++) {
		int min_seek = 999999, min_idx = -1;
		for (int j = 0; j < n; j++) {
			if (!visited[j]) {
				int seek = abs(request[j] - head);
				if (seek < min_seek) {
					min_seek = seek;
					min_idx = j;
				}
			}
		}
		visited[min_idx] = 1;
		total_seek_time += min_seek;
		head = request[min_idx];
		printf(" -> %d", head);
	}

	printf("\nTotal Seek Time: %d", total_seek_time);
	printf("\nAverage Seek Time: %.2f\n", (float)total_seek_time / n);
}

// Sorting function
void sort(int arr[], int n) {
	for (int i = 0; i < n - 1; i++)
		for (int j = i + 1; j < n; j++)
			if (arr[i] > arr[j]) {
				int temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
}

// SCAN (Elevator Algorithm)
void scan(int request[], int n, int head, int direction) {
	sort(request, n);
	int total_seek_time = 0, boundary = 199;
	int i, start;

	printf("\nSCAN SEEK SEQUENCE: %d", head);

	// Find the index where head should be in sorted order
	for (start = 0; start < n; start++)
		if (request[start] >= head)
			break;

	// Move in the given direction
	if (direction == 1) { // Moving right
		for (i = start; i < n; i++) {
			total_seek_time += abs(request[i] - head);
			head = request[i];
			printf(" -> %d", head);
		}
		total_seek_time += abs(boundary - head);
		head = boundary;
		printf(" -> %d", head);
		for (i = start - 1; i >= 0; i--) {
			total_seek_time += abs(request[i] - head);
			head = request[i];
			printf(" -> %d", head);
		}
	} else { // Moving left
		for (i = start - 1; i >= 0; i--) {
			total_seek_time += abs(request[i] - head);
			head = request[i];
			printf(" -> %d", head);
		}
		total_seek_time += abs(head - 0);
		head = 0;
		printf(" -> %d", head);
		for (i = start; i < n; i++) {
			total_seek_time += abs(request[i] - head);
			head = request[i];
			printf(" -> %d", head);
		}
	}

	printf("\nTotal Seek Time: %d", total_seek_time);
	printf("\nAverage Seek Time: %.2f\n", (float)total_seek_time / n);
}

void cscan(int request[], int n, int head, int direction) {
    sort(request, n);
    int total_seek_time = 0;
    int i, pos = 0;
    int boundary = 199; // Fixed disk size

    // Find head position in sorted request array
    while (pos < n && request[pos] < head) {
        pos++;
    }

    printf("\nC-SCAN SEEK SEQUENCE: %d", head);

    if (direction == 1) { // Moving right (up)
        for (i = pos; i < n; i++) {
            total_seek_time += abs(request[i] - head);
            head = request[i];
            printf(" -> %d", head);
        }
        if (head != boundary) {
            total_seek_time += abs(boundary - head);
            head = boundary;
            printf(" -> %d", head);
        }
        head = 0;
        printf(" -> %d", head);
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
        if (head != 0) {
            total_seek_time += abs(head - 0);
            head = 0;
            printf(" -> %d", head);
        }
        head = boundary;
        printf(" -> %d", head);
        for (i = n - 1; i >= pos; i--) {
            total_seek_time += abs(request[i] - head);
            head = request[i];
            printf(" -> %d", head);
        }
    }

    printf("\nTotal Seek Time: %d", total_seek_time);
    printf("\nAverage Seek Time: %.2f\n", (float)total_seek_time / n);
}


// C-LOOK Algorithm
void clook(int request[], int n, int head, int direction) {
    sort(request, n);
    int total_seek_time = 0;
    int i, start;

    printf("\nC-LOOK SEEK SEQUENCE: %d", head);

    // Find the index where head should be in sorted order
    for (start = 0; start < n; start++)
        if (request[start] >= head)
            break;

    if (direction == 1) { // Moving right
        for (i = start; i < n; i++) {
            total_seek_time += abs(request[i] - head);
            head = request[i];
            printf(" -> %d", head);
        }

        // After reaching the end, jump to the first request and continue
        if (start < n) {
            total_seek_time += abs(request[n - 1] - request[0]);  // Jump to the first request
            head = request[0];
            printf(" -> %d", head);
            for (i = 1; i < start; i++) {
                total_seek_time += abs(request[i] - head);
                head = request[i];
                printf(" -> %d", head);
            }
        }
    } else { // Moving left
        for (i = start - 1; i >= 0; i--) {
            total_seek_time += abs(request[i] - head);
            head = request[i];
            printf(" -> %d", head);
        }

        // After reaching the start, jump to the last request and continue
        if (start > 0) {
            total_seek_time += abs(request[0] - request[n - 1]);  // Jump to the last request
            head = request[n - 1];
            printf(" -> %d", head);
            for (i = n - 2; i >= start; i--) {
                total_seek_time += abs(request[i] - head);
                head = request[i];
                printf(" -> %d", head);
            }
        }
    }

    printf("\nTotal Seek Time: %d", total_seek_time);
    printf("\nAverage Seek Time: %.2f\n", (float)total_seek_time / n);
}

// LOOK Algorithm
void look(int request[], int n, int head, int direction) {
	sort(request, n);
	int total_seek_time = 0;
	int i, start;

	printf("\nLOOK SEEK SEQUENCE: %d", head);

	// Find the index where head should be in sorted order
	for (start = 0; start < n; start++)
		if (request[start] >= head)
			break;

	if (direction == 1) { // Move right first
		for (i = start; i < n; i++) {
			total_seek_time += abs(request[i] - head);
			head = request[i];
			printf(" -> %d", head);
		}
		for (i = start - 1; i >= 0; i--) {
			total_seek_time += abs(request[i] - head);
			head = request[i];
			printf(" -> %d", head);
		}
	} else { // Move left first
		for (i = start - 1; i >= 0; i--) {
			total_seek_time += abs(request[i] - head);
			head = request[i];
			printf(" -> %d", head);
		}
		for (i = start; i < n; i++) {
			total_seek_time += abs(request[i] - head);
			head = request[i];
			printf(" -> %d", head);
		}
	}

	printf("\nTotal Seek Time: %d", total_seek_time);
	printf("\nAverage Seek Time: %.2f\n", (float)total_seek_time / n);
}
/*
// C-LOOK Algorithm
void clook(int request[], int n, int head, int direction) {
    sort(request, n);
    int total_seek_time = 0;
    int i, start;

    printf("\nC-LOOK SEEK SEQUENCE: %d", head);

    // Find the index where head should be in sorted order
    for (start = 0; start < n; start++)
        if (request[start] >= head)
            break;

    if (direction == 1) { // Moving right
        for (i = start; i < n; i++) {
            total_seek_time += abs(request[i] - head);
            head = request[i];
            printf(" -> %d", head);
        }

        // After reaching the end, jump to the first request and continue
        if (start < n) {
            total_seek_time += abs(request[n - 1] - request[0]);  // Jump to the first request
            head = request[0];
            printf(" -> %d", head);
            for (i = 1; i < start; i++) {
                total_seek_time += abs(request[i] - head);
                head = request[i];
                printf(" -> %d", head);
            }
        }
    } else { // Moving left
        for (i = start - 1; i >= 0; i--) {
            total_seek_time += abs(request[i] - head);
            head = request[i];
            printf(" -> %d", head);
        }

        // After reaching the start, jump to the last request and continue
        if (start > 0) {
            total_seek_time += abs(request[0] - request[n - 1]);  // Jump to the last request
            head = request[n - 1];
            printf(" -> %d", head);
            for (i = n - 2; i >= start; i--) {
                total_seek_time += abs(request[i] - head);
                head = request[i];
                printf(" -> %d", head);
            }
        }
    }

    printf("\nTotal Seek Time: %d", total_seek_time);
    printf("\nAverage Seek Time: %.2f\n", (float)total_seek_time / n);
}

*/
// Main function
int main() {
	int n, head, choice, direction;
	int request[MAX];

	// Input: Number of disk requests
	printf("Enter number of disk requests: ");
	scanf("%d", &n);

	// Input: Disk request queue
	printf("Enter disk request queue: ");
	for (int i = 0; i < n; i++) {
		scanf("%d", &request[i]);
	}

	// Input: Initial head position
	printf("Enter initial head position: ");
	scanf("%d", &head);

	// Menu for disk scheduling algorithms
	while (1) {
		printf("\nDisk Scheduling Algorithms:\n");
		printf("1. FCFS\n2. SSTF\n3. SCAN\n4. C-SCAN\n5. LOOK\n6. C-LOOK\n0. Exit\n");
		printf("Enter your choice: ");
		scanf("%d", &choice);

		if (choice >= 3 && choice <= 6) {
			printf("Enter direction (1 for right, 0 for left): ");
			scanf("%d", &direction);
		}

		switch (choice) {
			case 1: fcfs(request, n, head); break;
			case 2: sstf(request, n, head); break;
			case 3: scan(request, n, head, direction); break;
			case 4: cscan(request, n, head, direction); break;
			case 5: look(request, n, head, direction); break;
			case 6: clook(request, n, head, direction); break;
			case 0: exit(0);
			default: printf("Invalid choice! Try again.\n");
		}
	}

}
