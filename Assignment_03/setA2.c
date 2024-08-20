/*
#include <stdio.h>
#include <stdlib.h>
#include <time.h> // Include for random number generation

struct job
{
    int at, bt, ct, tat, wt, st, tbt;
    char name[5]; // Name to hold "P0", "P1", ..., "Pn"
};

int n, i, j;
float avg_tat = 0;
float avg_wt = 0;
struct job *jobs; // Pointer for dynamic array of jobs

// Function to take input for jobs
void take_input()
{
    printf("Enter the number of jobs: ");
    scanf("%d", &n);

    // Allocate memory for n jobs
    jobs = (struct job *)malloc(n * sizeof(struct job));
    if (jobs == NULL)
    {
        printf("Memory allocation failed!");
        exit(1);
    }

    for (i = 0; i < n; i++)
    {
        printf("Enter the arrival time of job %d: ", i + 1);
        scanf("%d", &jobs[i].at);
        printf("Enter the first burst time of job %d: ", i + 1);
        scanf("%d", &jobs[i].bt);
        sprintf(jobs[i].name, "P%d", i); // Automatically generate process name
        jobs[i].tbt = jobs[i].bt;
        printf("\n");
    }
}

// Function to sort jobs by arrival time
void sort_by_arrival()
{
    struct job temp;
    for (i = 0; i < n - 1; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (jobs[i].at > jobs[j].at)
            {
                temp = jobs[i];
                jobs[i] = jobs[j];
                jobs[j] = temp;
            }
        }
    }
}

// Function to simulate Non-preemptive SJF scheduling
void process()
{
    int time = 0;
    int completed = 0;
    int min_index;
    int *completed_flag = (int *)malloc(n * sizeof(int));
    if (completed_flag == NULL)
    {
        printf("Memory allocation failed!");
        exit(1);
    }
    for (i = 0; i < n; i++)
        completed_flag[i] = 0; // Initialize completion flags to 0

    while (completed < n)
    {
        int min_burst = 1e9; // Set to a large value to find the minimum burst time
        min_index = -1;

        // Find the job with the shortest burst time that has arrived and not completed
        for (i = 0; i < n; i++)
        {
            if (jobs[i].at <= time && !completed_flag[i] && jobs[i].bt < min_burst)
            {
                min_burst = jobs[i].bt;
                min_index = i;
            }
        }

        if (min_index == -1)
        {
            time++; // If no job is available, increment time
            continue;
        }

        jobs[min_index].st = time;
        time += jobs[min_index].bt;
        jobs[min_index].ct = time;
        jobs[min_index].tat = jobs[min_index].ct - jobs[min_index].at;
        jobs[min_index].wt = jobs[min_index].tat - jobs[min_index].bt;
        completed_flag[min_index] = 1;
        completed++;

        // Generate next CPU-burst time randomly between 1 and 10
        jobs[min_index].bt = 1 + rand() % 10;

        printf("| %d %s ", jobs[min_index].st, jobs[min_index].name);
    }
    printf("| %d\n", time);

    free(completed_flag);
}

// Function to print the output table
void print_output()
{
    printf("\n\n");
    printf("---------------------------------------");
    printf("\n PName   AT   BT   TAT   WT ");
    printf("\n---------------------------------------");
    for (i = 0; i < n; i++)
    {
        printf("\n%s      %d    %d    %d    %d", jobs[i].name, jobs[i].at, jobs[i].bt, jobs[i].tat, jobs[i].wt);
        avg_tat += jobs[i].tat;
        avg_wt += jobs[i].wt;
    }
    printf("\n-----------------------------------------");
    printf("\nThe average Turn Around Time is: %.2f", avg_tat / n);
    printf("\nThe average Waiting Time is: %.2f", avg_wt / n);
    printf("\n-----------------------------------------\n");
}

int main()
{
    srand(time(NULL)); // Seed for random number generation

    take_input();
    sort_by_arrival();
    process();
    print_output();

    // Free the dynamically allocated memory
    free(jobs);

    return 0;
}
*/
/*
#include <stdio.h>
#include <stdlib.h>
#include <time.h> // Include for random number generation

struct job
{
    int at, bt, ct, tat, wt, st, tbt;
    char name[5]; // Name to hold "P0", "P1", ..., "Pn"
};

int n, i, j;
float avg_tat = 0;
float avg_wt = 0;
struct job *jobs; // Pointer for dynamic array of jobs

// Function to take input for jobs
void take_input()
{
    printf("Enter the number of jobs: ");
    scanf("%d", &n);

    // Allocate memory for n jobs
    jobs = (struct job *)malloc(n * sizeof(struct job));
    if (jobs == NULL)
    {
        printf("Memory allocation failed!");
        exit(1);
    }

    for (i = 0; i < n; i++)
    {
        printf("Enter the arrival time of job %d: ", i + 1);
        scanf("%d", &jobs[i].at);
        printf("Enter the first burst time of job %d: ", i + 1);
        scanf("%d", &jobs[i].bt);
        sprintf(jobs[i].name, "P%d", i); // Automatically generate process name
        jobs[i].tbt = jobs[i].bt;
        printf("\n");
    }
}

// Function to sort jobs by arrival time
void sort()
{
    struct job temp;
    for (i = 0; i < n - 1; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (jobs[i].at > jobs[j].at)
            {
                temp = jobs[i];
                jobs[i] = jobs[j];
                jobs[j] = temp;
            }
        }
    }
}

// Function to simulate Non-preemptive SJF scheduling
void process()
{
    int time = 0;
    int completed = 0;
    int indx;
    int *flag = (int *)malloc(n * sizeof(int));
    if (flag == NULL)
    {
        printf("Memory allocation failed!");
        exit(1);
    }
    for (i = 0; i < n; i++)
        flag[i] = 0; // Initialize completion flags to 0

    while (completed < n)
    {
        int burst = 1e9; // Set to a large value to find the minimum burst time
        indx = -1;

        // Find the job with the shortest burst time that has arrived and not completed
        for (i = 0; i < n; i++)
        {
            if (jobs[i].at <= time && !flag[i] && jobs[i].bt < burst)
            {
                burst = jobs[i].bt;
                indx = i;
            }
        }

        if (indx == -1)
        {
            time++; // If no job is available, increment time
            continue;
        }

        jobs[indx].st = time;
        time += jobs[indx].bt;
        jobs[indx].ct = time;
        jobs[indx].tat = jobs[indx].ct - jobs[indx].at;
        jobs[indx].wt = jobs[indx].tat - jobs[indx].tbt;
        flag[indx] = 1;
        completed++;

        // Generate next CPU-burst time randomly between 1 and 10
        jobs[indx].bt = 1 + rand() % 10;

        printf("| %d %s ", jobs[indx].st, jobs[indx].name);
    }
    printf("| %d\n", time);

    free(flag);
}

// Function to print the output table
void print_output()
{
    printf("\n\n");
    printf("---------------------------------------");
    printf("\n PName   AT   BT   TAT   WT ");
    printf("\n---------------------------------------");
    for (i = 0; i < n; i++)
    {
        printf("\n%s      %d    %d    %d    %d", jobs[i].name, jobs[i].at, jobs[i].tbt, jobs[i].tat, jobs[i].wt);
        avg_tat += jobs[i].tat;
        avg_wt += jobs[i].wt;
    }
    printf("\n-----------------------------------------");
    printf("\nThe average Turn Around Time is: %.2f", avg_tat / n);
    printf("\nThe average Waiting Time is: %.2f", avg_wt / n);
    printf("\n-----------------------------------------\n");
}

int main()
{
    srand(time(NULL)); // Seed for random number generation

    take_input();
    sort();
    process();
    print_output();

    // Free the dynamically allocated memory
    free(jobs);

    return 0;
}
*/




#include <stdio.h>
#include <stdlib.h>
#include <time.h> // Include for random number generation

struct job
{
    int at, bt, ct, tat, wt, st, tbt;
    char name[5]; // Name to hold "P0", "P1", ..., "Pn"
};

int n, i, j;
float avg_tat = 0;
float avg_wt = 0;
struct job *jobs; // Pointer for dynamic array of jobs

// Function to take input for jobs
void take_input()
{
    printf("Enter the number of jobs: ");
    scanf("%d", &n);

    // Allocate memory for n jobs
    jobs = (struct job *)malloc(n * sizeof(struct job));
    if (jobs == NULL)
    {
        printf("Memory allocation failed!");
        exit(1);
    }

    for (i = 0; i < n; i++)
    {
        printf("Enter the arrival time of job %d: ", i + 1);
        scanf("%d", &jobs[i].at);
        printf("Enter the first burst time of job %d: ", i + 1);
        scanf("%d", &jobs[i].bt);
        sprintf(jobs[i].name, "P%d", i); // Automatically generate process name
        jobs[i].tbt = jobs[i].bt;
        printf("\n");
    }
}

// Function to sort jobs by arrival time
void sort()
{
    struct job temp;
    for (i = 0; i < n - 1; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (jobs[i].at > jobs[j].at)
            {
                temp = jobs[i];
                jobs[i] = jobs[j];
                jobs[j] = temp;
            }
        }
    }
}

// Function to simulate Non-preemptive SJF scheduling
void process()
{
    int time = 0;
    int completed = 0;
    int indx;
    int *flag = (int *)malloc(n * sizeof(int));
    if (flag == NULL)
    {
        printf("Memory allocation failed!");
        exit(1);
    }
    for (i = 0; i < n; i++)
        flag[i] = 0; // Initialize completion flags to 0

    // Initialize Gantt chart representation
    int gantt_chart_length = 0;
    int *gantt_chart = (int *)malloc(n * sizeof(int));
    if (gantt_chart == NULL)
    {
        printf("Memory allocation failed!");
        exit(1);
    }

    while (completed < n)
    {
        int burst = 1e9; // Set to a large value to find the minimum burst time
        indx = -1;

        // Find the job with the shortest burst time that has arrived and not completed
        for (i = 0; i < n; i++)
        {
            if (jobs[i].at <= time && !flag[i] && jobs[i].bt < burst)
            {
                burst = jobs[i].bt;
                indx = i;
            }
        }

        if (indx == -1)
        {
            time++; // If no job is available, increment time
            continue;
        }

        jobs[indx].st = time;
        time += jobs[indx].bt;
        jobs[indx].ct = time;
        jobs[indx].tat = jobs[indx].ct - jobs[indx].at;
        jobs[indx].wt = jobs[indx].tat - jobs[indx].tbt;
        flag[indx] = 1;
        completed++;

        // Generate next CPU-burst time randomly between 1 and 10
        jobs[indx].bt = 1 + rand() % 10;

        // Record Gantt chart
        gantt_chart[gantt_chart_length++] = jobs[indx].st;
        gantt_chart[gantt_chart_length++] = time;
        printf("| %d %s ", jobs[indx].st, jobs[indx].name);
    }
    printf("| %d\n", time);

    // Print Gantt chart
    printf("\nGantt Chart:\n");
    for (i = 0; i < gantt_chart_length; i += 2)
    {
        printf("| %d-%d %s ", gantt_chart[i], gantt_chart[i + 1], jobs[i / 2].name);
    }
    printf("|\n");

    free(flag);
    free(gantt_chart);
}

// Function to print the output table
void print_output()
{
    printf("\n\n");
    printf("---------------------------------------");
    printf("\n PName   AT   BT   TAT   WT ");
    printf("\n---------------------------------------");
    for (i = 0; i < n; i++)
    {
        printf("\n%s      %d    %d    %d    %d", jobs[i].name, jobs[i].at, jobs[i].tbt, jobs[i].tat, jobs[i].wt);
        avg_tat += jobs[i].tat;
        avg_wt += jobs[i].wt;
    }
    printf("\n-----------------------------------------");
    printf("\nThe average Turn Around Time is: %.2f", avg_tat / n);
    printf("\nThe average Waiting Time is: %.2f", avg_wt / n);
    printf("\n-----------------------------------------\n");
}

int main()
{
    srand(time(NULL)); // Seed for random number generation

    take_input();
    sort();
    process();
    print_output();

    // Free the dynamically allocated memory
    free(jobs);

    return 0;
}
