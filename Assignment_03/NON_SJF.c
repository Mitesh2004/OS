#include <stdio.h>

// Function to swap two integers
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to sort processes by burst time
void sortByBurstTime(int at[], int bt[], int pid[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (bt[i] > bt[j])
            {
                // Swap burst times
                swap(&bt[i], &bt[j]);
                // Swap arrival times to maintain the relation
                swap(&at[i], &at[j]);
                // Swap process IDs to maintain the relation
                swap(&pid[i], &pid[j]);
            }
        }
    }
}

int main()
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int at[n], bt[n], ct[n], wt[n], tat[n], pid[n];
    float wtavg = 0, tatavg = 0;

    // Input arrival time, burst time, and process IDs
    printf("Enter the arrival time, burst time, and process ID for each process:\n");
    for (int i = 0; i < n; i++)
    {
        pid[i] = i + 1; // Process ID
        printf("Process %d:\nArrival Time: ", i + 1);
        scanf("%d", &at[i]);
        printf("Burst Time: ");
        scanf("%d", &bt[i]);

        printf("----------------\n");
    }

    // Sort processes by burst time
    sortByBurstTime(at, bt, pid, n);

    // Initialize variables
    int time = 0;
    int completed = 0;
    int minIndex;
    int isCompleted[n];
    for (int i = 0; i < n; i++)
        isCompleted[i] = 0;

    // Calculate completion time, turnaround time, and waiting time
    while (completed < n)
    {
        minIndex = -1;
        for (int i = 0; i < n; i++)
        {
            if (!isCompleted[i] && at[i] <= time)
            {
                if (minIndex == -1 || bt[i] < bt[minIndex])
                {
                    minIndex = i;
                }
            }
        }

        if (minIndex != -1)
        {
            ct[minIndex] = time + bt[minIndex];
            tat[minIndex] = ct[minIndex] - at[minIndex];
            wt[minIndex] = tat[minIndex] - bt[minIndex];
            wtavg += wt[minIndex];
            tatavg += tat[minIndex];
            time += bt[minIndex];
            isCompleted[minIndex] = 1;
            completed++;
        }
        else
        {
            time++; // If no process is ready, increment time
        }
    }

    // Calculate averages
    wtavg /= n;
    tatavg /= n;

    // Print results
    printf("\nProcess ID\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", pid[i], at[i], bt[i], ct[i], tat[i], wt[i]);
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