#include <stdio.h>

struct pro {
    int no, at, bt, ct, tat, wt;
};

struct pro get(int i) {
    struct pro p;
    p.no = i;
    printf("\nProcess No: %d\n", i);
    printf("Enter Arrival Time: ");
    scanf("%d", &p.at);
    printf("Enter Burst Time: ");
    scanf("%d", &p.bt);
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

void FCFSprocess(struct pro p[], int n) {
    int ct = 0;
    for (int i = 0; i < n; i++) {
        if (i == 0 || ct < p[i].at) {
            ct = p[i].at;
        }
        ct += p[i].bt;
        p[i].ct = ct;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
    }
}

void gantchart(struct pro p[], int n) {
    printf("\nGantt Chart:\n|");
    for (int i = 0; i < n; i++) {
        printf("\tP%d\t|", p[i].no);
    }
    printf("\n0");
    for (int i = 0; i < n; i++) {
        printf("\t\t%d", p[i].ct);
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
    printf("FCFS Scheduling Algorithm\n");
    printf("Enter Number of Processes: ");
    scanf("%d", &n);
    struct pro p[n];
    for (int i = 0; i < n; i++) {
        p[i] = get(i + 1);
    }
    sort(p, n);
    FCFSprocess(p, n);
    gantchart(p, n);
    output(p, n);
    return 0;
}
