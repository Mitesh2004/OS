#include <stdio.h>
#include <stdlib.h>
#include <time.h> // Include for random number generation

struct job {
    int at, bt, ct, tat, wt, st, rt, tbt;
    char name[5]; // Name to hold "P0", "P1", ..., "Pn"
};

int n, i, j;
float avg_tat = 0;
float avg_wt = 0;
struct job *jobs; // Pointer for dynamic array of jobs

// Function to take input for jobs
void take_input() {
    printf("Enter the number of jobs: ");
    scanf("%d", &n);

    // Allocate memory for n jobs
    jobs = (struct job *)malloc(n * sizeof(struct job));
    if (jobs == NULL) {
        printf("Memory allocation failed!");
        exit(1);
    }

    for (i = 0; i < n; i++) {
        printf("Enter the arrival time of job %d: ", i + 1);
        scanf("%d", &jobs[i].at);
        printf("Enter the first burst time of job %d: ", i + 1);
        scanf("%d", &jobs[i].bt);
        sprintf(jobs[i].name, "P%d", i); // Automatically generate process name
        jobs[i].tbt = jobs[i].bt;
        jobs[i].rt = jobs[i].bt; // Remaining time initially equals burst time
        printf("\n");
    }
}

// Function to sort jobs by arrival time
void sort() {
    struct job temp;
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (jobs[i].at > jobs[j].at) {
                temp = jobs[i];
                jobs[i] = jobs[j];
                jobs[j] = temp;
            }
        }
    }
}

// Function to simulate Preemptive SJF scheduling
void process() {
    int time = 0;
    int completed = 0;
    int indx;
    int *flag = (int *)malloc(n * sizeof(int));
    if (flag == NULL) {
        printf("Memory allocation failed!");
        exit(1);
    }
    for (i = 0; i < n; i++)
        flag[i] = 0; // Initialize completion flags to 0

    // Initialize Gantt chart representation
    int gantt_chart_length = 0;
    int *gantt_chart = (int *)malloc(n * sizeof(int));
    if (gantt_chart == NULL) {
        printf("Memory allocation failed!");
        exit(1);
    }

    while (completed < n) {
        int min_rt = 1e9; // Set to a large value to find the minimum remaining time
        indx = -1;

        // Find the job with the shortest remaining time that has arrived and not completed
        for (i = 0; i < n; i++) {
            if (jobs[i].at <= time && !flag[i] && jobs[i].rt < min_rt) {
                min_rt = jobs[i].rt;
                indx = i;
            }
        }

        if (indx == -1) {
            time++; // If no job is available, increment time
            continue;
        }

        // Record Gantt chart
        gantt_chart[gantt_chart_length++] = time;

        // Process the job
        jobs[indx].rt--;
        time++;

        // If the job is completed
        if (jobs[indx].rt == 0) {
            jobs[indx].ct = time;
            jobs[indx].tat = jobs[indx].ct - jobs[indx].at;
            jobs[indx].wt = jobs[indx].tat - jobs[indx].tbt;
            flag[indx] = 1;
            completed++;

            // Generate next CPU-burst time randomly between 1 and 10
            jobs[indx].bt = 1 + rand() % 10;
            jobs[indx].rt = jobs[indx].bt;

            // Record Gantt chart
            gantt_chart[gantt_chart_length++] = time;
            printf("| %d %s ", gantt_chart[gantt_chart_length - 2], jobs[indx].name);
        }
    }
    printf("| %d\n", time);

    // Print Gantt chart
    printf("\nGantt Chart:\n");
    for (i = 0; i < gantt_chart_length; i += 2) {
        printf("| %d-%d %s ", gantt_chart[i], gantt_chart[i + 1], jobs[i / 2].name);
    }
    printf("|\n");

    free(flag);
    free(gantt_chart);
}

// Function to print the output table
void print_output() {
    printf("\n\n");
    printf("---------------------------------------");
    printf("\n PName   AT   BT   TAT   WT ");
    printf("\n---------------------------------------");
    for (i = 0; i < n; i++) {
        printf("\n%s      %d    %d    %d    %d", jobs[i].name, jobs[i].at, jobs[i].tbt, jobs[i].tat, jobs[i].wt);
        avg_tat += jobs[i].tat;
        avg_wt += jobs[i].wt;
    }
    printf("\n-----------------------------------------");
    printf("\nThe average Turn Around Time is: %.2f", avg_tat / n);
    printf("\nThe average Waiting Time is: %.2f", avg_wt / n);
    printf("\n-----------------------------------------\n");
}

int main() {
    srand(time(NULL)); // Seed for random number generation

    take_input();
    sort();
    process();
    print_output();

    // Free the dynamically allocated memory
    free(jobs);

    return 0;
}