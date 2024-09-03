#include <stdio.h>
#include <stdbool.h>

struct pro {
    int no, at, bt, ct, tat, wt, rt; // rt is the remaining time
};

struct pro get(int i) {
    struct pro p;
    p.no = i;
    printf("\nProcess No: %d\n", i);
    printf("Enter Arrival Time: ");
    scanf("%d", &p.at);
    printf("Enter Burst Time: ");
    scanf("%d", &p.bt);
    p.rt = p.bt; // Initialize remaining time with burst time
    return p;
}

// Function to swap two processes
void swap(struct pro *a, struct pro *b) {
    struct pro temp = *a;
    *a = *b;
    *b = temp;
}

void sort(struct pro p[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].at > p[j + 1].at) {
                swap(&p[j], &p[j + 1]);
            }
        }
    }
}

void RoundRobinProcess(struct pro p[], int n, int quantum) {
    int ct = 0, count = 0;
    bool done;
    while (count < n) {
        done = false;
        for (int i = 0; i < n; i++) {
            if (p[i].at <= ct && p[i].rt > 0) {
                done = true;
                int exec_time = (p[i].rt > quantum) ? quantum : p[i].rt;
                ct += exec_time;
                p[i].rt -= exec_time;
                if (p[i].rt == 0) {
                    p[i].ct = ct;
                    p[i].tat = p[i].ct - p[i].at;
                    p[i].wt = p[i].tat - p[i].bt;
                    count++;
                }
            }
        }
        if (!done) {
            ct++;
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
    int n, quantum;
    printf("Round Robin Scheduling Algorithm\n");
    printf("Enter Number of Processes: ");
    scanf("%d", &n);
    struct pro p[n];
    for (int i = 0; i < n; i++) {
        p[i] = get(i + 1);
    }
    sort(p, n);
    printf("Enter Time Quantum: ");
    scanf("%d", &quantum);
    RoundRobinProcess(p, n, quantum);
    gantchart(p, n);
    output(p, n);
    return 0;
}