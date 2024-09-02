#include <stdio.h>

int main()
{
    int n, qt;

    // Input number of processes and time quantum
    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter time quantum: ");
    scanf("%d", &qt);

    int bt[n], rembt[n], wt[n], tat[n], at[n], ct[n];
    int t = 0, total_wt = 0, total_tat = 0;

    // Input burst time and arrival time for each process
    printf("Enter arrival times and burst times for each process:\n");
    for (int i = 0; i < n; i++)
    {
        printf("Process %d:\nArrival Time: ", i + 1);
        scanf("%d", &at[i]);
        printf("Burst Time: ");
        scanf("%d", &bt[i]);
        rembt[i] = bt[i]; // Initialize remaining burst time
    }

    // Round Robin Scheduling
    while (1)
    {
        int done = 1; // Flag to check if all processes are done
        for (int i = 0; i < n; i++)
        {
            if (rembt[i] > 0)
            {
                done = 0; // Not all processes are done
                if (rembt[i] > qt)
                {
                    t += qt;
                    rembt[i] -= qt;
                }
                else
                {
                    t += rembt[i];
                    ct[i] = t;                 // Set completion time
                    wt[i] = t - at[i] - bt[i]; // Calculate waiting time
                    rembt[i] = 0;
                }
            }
        }
        if (done)
            break;
    }

    // Calculate turnaround time and total waiting time
    for (int i = 0; i < n; i++)
    {
        tat[i] = ct[i] - at[i];
        total_wt += wt[i];
        total_tat += tat[i];
    }

    // Output results
    printf("\nProcess\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    printf("\nAverage waiting time = %.2f\n", (float)total_wt / n);
    printf("Average turnaround time = %.2f\n", (float)total_tat / n);
    // Print Gantt chart
    printf("\nGantt Chart:\n");
    for (int i = 0; i < n; i++)
    {
        printf("|\tP%d\t", i + 1);
    }
    printf("|\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t\t", i == 0 ? at[0] : ct[i - 1]);
    }
    printf("%d\n", ct[n - 1]);

    return 0;
}