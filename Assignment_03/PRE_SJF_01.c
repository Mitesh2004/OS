#include <stdio.h>
#include <limits.h>

struct pro {
    int no, at, bt, ct, tat, wt, rem_bt;
};

struct pro get(int i) {
    struct pro p;
    p.no = i;
    printf("\nProcess No: %d\n", i);
    printf("Enter Arrival Time: ");
    scanf("%d", &p.at);
    printf("Enter Burst Time: ");
    scanf("%d", &p.bt);
    p.rem_bt = p.bt; // Initialize remaining burst time
    return p;
}

// Function to swap two processes
void swap(struct pro *a, struct pro *b) {
    struct pro temp = *a;
    *a = *b;
    *b = temp;
}

// Sort processes by Arrival Time
void sort(struct pro p[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].at > p[j + 1].at) {
                swap(&p[j], &p[j + 1]);
            }
        }
    }
}

// Function to process Preemptive SJF Scheduling
void SJFProcess(struct pro p[], int n) {
    int time = 0, completed = 0;
    int minIdx;
    int done[n];
    for (int i = 0; i < n; i++) done[i] = 0; // Initialize done array

    while (completed < n) {
        minIdx = -1;
        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && p[i].rem_bt > 0 && (minIdx == -1 || p[i].rem_bt < p[minIdx].rem_bt)) {
                minIdx = i;
            }
        }
        if (minIdx != -1) {
            p[minIdx].rem_bt--;
            time++;
            if (p[minIdx].rem_bt == 0) {
                p[minIdx].ct = time;
                p[minIdx].tat = p[minIdx].ct - p[minIdx].at;
                p[minIdx].wt = p[minIdx].tat - p[minIdx].bt;
                done[minIdx] = 1;
                completed++;
            }
        } else {
            time++;
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
    printf("Preemptive SJF Scheduling Algorithm\n");
    printf("Enter Number of Processes: ");
    scanf("%d", &n);
    struct pro p[n];
    for (int i = 0; i < n; i++) {
        p[i] = get(i + 1);
    }
    sort(p, n);
    SJFProcess(p, n);
    gantchart(p, n);
    output(p, n);
    return 0;
}