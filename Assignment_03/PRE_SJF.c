#include <stdio.h>
#include <limits.h>

int main()
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int pid[n], at[n], bt[n], ct[n], wt[n], tat[n];
    float wtavg = 0, tatavg = 0;

    int remaining_bt[n], time = 0, completed = 0, min_index;

    // Input arrival time and burst time for each process
    printf("Enter arrival time and burst time for each process:\n");
    for (int i = 0; i < n; i++)
    {
        pid[i] = i + 1;
        printf("Process %d\nArrival Time: ", pid[i]);
        scanf("%d", &at[i]);
        printf("Burst Time: ");
        scanf("%d", &bt[i]);
        remaining_bt[i] = bt[i]; // Initialize remaining burst time
    }

    // Process scheduling loop
    while (completed < n)
    {
        int min_bt = INT_MAX;
        min_index = -1;

        for (int j = 0; j < n; j++)
        {
            if (at[j] <= time && remaining_bt[j] > 0 && remaining_bt[j] < min_bt)
            {
                min_bt = remaining_bt[j];
                min_index = j;
            }
        }

        if (min_index != -1)
        {
            remaining_bt[min_index]--;
            time++;

            if (remaining_bt[min_index] == 0)
            {
                completed++;
                ct[min_index] = time;
                tat[min_index] = ct[min_index] - at[min_index];
                wt[min_index] = tat[min_index] - bt[min_index];
                wtavg += wt[min_index];
                tatavg += tat[min_index];
            }
        }
        else
        {
            time++;
        }
    }

    // Calculate averages
    wtavg /= n;
    tatavg /= n;

    // Print results
    printf("\nProcess\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", pid[i], at[i], bt[i], ct[i], tat[i], wt[i]);
    }
    printf("\nAverage Waiting Time: %.2f", wtavg);
    printf("\nAverage Turnaround Time: %.2f", tatavg);

    // Print Gantt chart
    printf("\nGantt Chart:\n");
    for (int i = 0; i < n; i++)
    {
        printf("|\tP%d\t", pid[i]);
    }
    printf("|\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t\t", i == 0 ? at[0] : ct[i - 1]);
    }
    printf("%d\n", ct[n - 1]);

    return 0;
}