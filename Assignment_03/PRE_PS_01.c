#include <stdio.h>
#include <limits.h>

struct pro {
    int no, at, bt, ct, tat, wt, rem_bt, priority;
};

struct pro get(int i) {
    struct pro p;
    p.no = i;
    printf("\nProcess No: %d\n", i);
    printf("Enter Arrival Time: ");
    scanf("%d", &p.at);
    printf("Enter Burst Time: ");
    scanf("%d", &p.bt);
    printf("Enter Priority (lower number indicates higher priority): ");
    scanf("%d", &p.priority);
    p.rem_bt = p.bt; // Initialize remaining burst time
    return p;
}

// Function to swap two processes
void swap(struct pro *a, struct pro *b) {
    struct pro temp = *a;
    *a = *b;
    *b = temp;
}

// Sort processes by Arrival Time and Priority
void sort(struct pro p[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].at > p[j + 1].at || 
                (p[j].at == p[j + 1].at && p[j].priority > p[j + 1].priority)) {
                swap(&p[j], &p[j + 1]);
            }
        }
    }
}

// Function to process Preemptive Priority Scheduling
void PSProcess(struct pro p[], int n) {
    int time = 0, completed = 0;
    int CP = -1;
    int done[n];
    for (int i = 0; i < n; i++) done[i] = 0; // Initialize done array

    while (completed < n) {
        int minIdx = -1;
        
        // Find the process with the highest priority that is ready to execute
        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && p[i].rem_bt > 0 && 
                (minIdx == -1 || p[i].priority < p[minIdx].priority)) {
                minIdx = i;
            }
        }

        if (minIdx != -1) {
            // If a new process is selected, update the current process
            if (CP != minIdx) {
                CP = minIdx;
            }
            // Execute the current process
            p[CP].rem_bt--;
            time++;

            // If the process is completed
            if (p[CP].rem_bt == 0) {
                p[CP].ct = time;
                p[CP].tat = p[CP].ct - p[CP].at;
                p[CP].wt = p[CP].tat - p[CP].bt;
                done[CP] = 1;
                completed++;
            }
        } else {
            time++; // Increment time if no process is ready
        }
    }
}

void gantchart(struct pro p[], int n) {
    printf("\nGantt Chart:\n|");
    for (int i = 0; i < n; i++) {
        printf("\tP%d\t|", p[i].no);
    }
    printf("\n0\t");
    for (int i = 0; i < n; i++) {
        printf("\t%d\t", p[i].ct);
    }
    printf("\n");
}

void output(struct pro p[], int n) {
    float avgtat = 0, avgwt = 0;
    printf("\nProcessNo\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        avgtat += p[i].tat;
        avgwt += p[i].wt;
        printf("P%d\t\t%d\t%d\t%d\t%d\t%d\n", p[i].no, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }
    avgtat /= n;
    avgwt /= n;
    printf("\nAverage TurnAround Time = %.2f\nAverage Waiting Time = %.2f\n", avgtat, avgwt);
}

int main() {
    int n;
    printf("Preemptive Priority Scheduling Algorithm\n");
    printf("Enter Number of Processes: ");
    scanf("%d", &n);
    struct pro p[n];
    for (int i = 0; i < n; i++) {
        p[i] = get(i + 1);
    }
    sort(p, n);
    PSProcess(p, n);
    gantchart(p, n);
    output(p, n);
    return 0;
}