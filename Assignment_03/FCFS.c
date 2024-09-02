#include <stdio.h>
// Function to swap two processes
void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}
// Function to sort processes by arrival time
void sort(int at[], int bt[], int n){
    for (int i = 0; i < n - 1; i++){
        for (int j = i + 1; j < n; j++){
            if (at[i] > at[j]){
                // Swap arrival times
                swap(&at[i], &at[j]);
                // Swap burst times to maintain the relation
                swap(&bt[i], &bt[j]);
            }
        }
    }
}
int main(){
    int n, i;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    int at[n], bt[n], ct[n], wt[n], tat[n]; // Arrival time, burst time, completion time, waiting time, turnaround time
    float wtavg = 0, tatavg = 0;
    // Input arrival time and burst time for each process
    printf("Enter the arrival time and burst time for each process:\n");
    for (i = 0; i < n; i++){
        printf("Process %d:\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &at[i]);
        printf("Burst Time: ");
        scanf("%d", &bt[i]);
        printf("----------------\n");
    }
    // Sort processes by arrival time
    sort(at, bt, n);
    // Calculate completion time, turnaround time, and waiting time
    for (i = 0; i < n; i++){
        // Calculate completion time
        if (i == 0){
            // For the first process
            ct[i] = at[i] + bt[i];
        }else{
            if (at[i] > ct[i - 1]){
                ct[i] = at[i] + bt[i];
            }else{
                ct[i] = ct[i - 1] + bt[i];
            }
        }
        // Calculate turnaround time
        tat[i] = ct[i] - at[i];
        // Calculate waiting time
        wt[i] = tat[i] - bt[i];
        // Accumulate waiting time and turnaround time for average calculation
        wtavg += wt[i];
        tatavg += tat[i];
    }
    // Calculate averages
    wtavg /= n;
    tatavg /= n;
    // Print results
    printf("\nProcess\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (i = 0; i < n; i++){
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, at[i], bt[i], ct[i], tat[i], wt[i]);
    }
    printf("\nAverage Waiting Time: %.2f", wtavg);
    printf("\nAverage Turnaround Time: %.2f", tatavg);
    // Print Gantt chart
    printf("\nGantt Chart:\n");
    for (i = 0; i < n; i++){
        printf("|\tP%d\t", i + 1);
    }
    printf("|\n");
    for (i = 0; i < n; i++){
        printf("%d\t\t", i == 0 ? at[0] : ct[i - 1]);
    }
    printf("%d\n", ct[n - 1]);
    return 0;
}