#include <stdio.h>

// Function to swap two integers
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to sort processes by arrival time and burst time
void sort(int n, int at[], int bt[], int pid[])
{
    int i, j;
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (at[j] > at[j + 1] || (at[j] == at[j + 1] && bt[j] > bt[j + 1]))
            {
                // Swap arrival times
                swap(&at[j], &at[j + 1]);

                // Swap burst times
                swap(&bt[j], &bt[j + 1]);

                // Swap process IDs
                swap(&pid[j], &pid[j + 1]);
            }
        }
    }
}

int main()
{
    int n, i;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int pid[n], at[n], bt[n], ct[n], wt[n], tat[n];
    float wtavg = 0, tatavg = 0;

    printf("Enter the arrival time and burst time for each process:\n");
    for (i = 0; i < n; i++)
    {
        pid[i] = i + 1; // Process ID
        printf("Process %d:\n", pid[i]);
        printf("Arrival Time: ");
        scanf("%d", &at[i]);
        printf("Burst Time: ");
        scanf("%d", &bt[i]);
    }

    // Sort processes by arrival time, and by burst time if arrival times are the same
    sort(n, at, bt, pid);

    // Initialize completion time array
    for (i = 0; i < n; i++)
    {
        ct[i] = 0;
    }

    // Calculate completion time, turnaround time, and waiting time
    for (i = 0; i < n; i++)
    {
        // Use the completion time of the previous process to calculate the current completion time
        if (i == 0 || ct[i - 1] < at[i])
        {
            ct[i] = at[i] + bt[i];
        }
        else
        {
            ct[i] = ct[i - 1] + bt[i];
        }

        tat[i] = ct[i] - at[i]; // Turnaround time
        wt[i] = tat[i] - bt[i]; // Waiting time

        wtavg += wt[i];
        tatavg += tat[i];
    }

    // Calculate averages
    wtavg /= n;
    tatavg /= n;

    // Print results
    printf("\nProcess\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (i = 0; i < n; i++)
    {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", pid[i], at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    printf("\nAverage Waiting Time: %.2f", wtavg);
    printf("\nAverage Turnaround Time: %.2f", tatavg);

    // Print Gantt chart
    printf("\nGantt Chart:\n");
    for (i = 0; i < n; i++)
    {
        printf("|\tP%d\t", pid[i]);
    }
    printf("|\n");

    for (i = 0; i < n; i++)
    {
        printf("%d\t\t", i == 0 ? at[0] : ct[i - 1]);
    }
    printf("%d\n", ct[n - 1]);

    return 0;
}