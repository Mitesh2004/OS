#include <stdio.h>
#include <limits.h>

// Function to swap two integers
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to sort processes by priority and arrival time
void sort(int n, int pid[], int bt[], int priority[], int at[])
{
    int i, j;
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (priority[j] > priority[j + 1] || (priority[j] == priority[j + 1] && at[j] > at[j + 1]))
            {
                // Swap priority
                swap(&priority[j], &priority[j + 1]);

                // Swap burst time
                swap(&bt[j], &bt[j + 1]);

                // Swap process ID
                swap(&pid[j], &pid[j + 1]);

                // Swap arrival time
                swap(&at[j], &at[j + 1]);
            }
        }
    }
}

int main()
{
    int n, i;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int pid[n], bt[n], original_bt[n], priority[n], at[n], ct[n];
    int wt[n], tat[n];
    float wtavg = 0, tatavg = 0;

    // Input burst time, priority, and arrival time for each process
    printf("Enter the burst time, priority, and arrival time for each process:\n");
    for (i = 0; i < n; i++)
    {
        pid[i] = i + 1; // Process ID
        printf("Process %d\nArrival Time: ", pid[i]);
        scanf("%d", &at[i]);
        printf("Burst Time: ");
        scanf("%d", &bt[i]);
        original_bt[i] = bt[i]; // Save original burst time
        printf("Priority: ");
        scanf("%d", &priority[i]);
        printf("----------------\n");
    }

    // Sort processes by priority and then by arrival time
    sort(n, pid, bt, priority, at);

    int time = 0;        // Current time
    int completed = 0;   // Count of completed processes
    int remaining_bt[n]; // Array to keep track of remaining burst times

    for (i = 0; i < n; i++)
    {
        remaining_bt[i] = bt[i];
    }

    while (completed < n)
    {
        int idx = -1;
        int highest_priority = INT_MAX;

        // Find the highest priority process that is ready to run
        for (i = 0; i < n; i++)
        {
            if (at[i] <= time && priority[i] < highest_priority && remaining_bt[i] > 0)
            {
                highest_priority = priority[i];
                idx = i;
            }
        }

        if (idx != -1)
        {
            // Execute the process for 1 unit of time
            remaining_bt[idx]--;
            time++;

            if (remaining_bt[idx] == 0)
            {
                // Process idx is completed
                ct[idx] = time;                        // Completion time of the selected process
                tat[idx] = ct[idx] - at[idx];          // Turnaround time
                wt[idx] = tat[idx] - original_bt[idx]; // Waiting time
                completed++;                           // Increment completed processes count
            }
        }
        else
        {
            time++; // No process is ready, increment time
        }
    }

    // Calculate averages
    for (i = 0; i < n; i++)
    {
        wtavg += wt[i];
        tatavg += tat[i];
    }
    wtavg /= n;
    tatavg /= n;

    // Print results
    printf("\nProcess\tBurst Time\tPriority\tArrival Time\tWaiting Time\tTurnaround Time\tCompletion Time\n");
    for (i = 0; i < n; i++)
    {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", pid[i], original_bt[i], priority[i], at[i], wt[i], tat[i], ct[i]);
    }

    printf("\nAverage Waiting Time: %.2f", wtavg);
    printf("\nAverage Turnaround Time: %.2f", tatavg);

    // Print Gantt chart
    printf("\nGantt Chart:\n");
    int gantt_time = 0;
    for (i = 0; i < n; i++)
    {
        printf("|\tP%d\t", pid[i]);
        gantt_time += original_bt[i];
    }
    printf("|\n0\t\t");
    gantt_time = 0;
    for (i = 0; i < n; i++)
    {
        gantt_time += original_bt[i];
        printf("%d\t\t", gantt_time);
    }
    printf("\n");

    return 0;
}