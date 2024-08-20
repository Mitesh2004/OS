#include<stdio.h>
#include<stdlib.h>  // Include for dynamic memory allocation

struct job 
{
	int at, bt, ct, tat, wt, st, tbt;
	char name[5];  // Name to hold "P0", "P1", ..., "Pn"
};

int n, i, j;
float avg_tat = 0;
float avg_wt = 0;
struct job *jobs;  // Pointer for dynamic array of jobs

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
		printf("Enter the burst time of job %d: ", i + 1);
		scanf("%d", &jobs[i].bt);
		sprintf(jobs[i].name, "P%d", i);  // Automatically generate process name
		jobs[i].tbt = jobs[i].bt;
		printf("\n");
	}
}

// Function to sort the jobs by arrival time
void sort() 
{
	struct job temp;
	for (i = 0; i < n; i++) 
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

// Function to calculate the turnaround time and waiting time
void process() 
{
	int time = jobs[0].at;
	for (j = 0; j < n; j++) 
	{
		jobs[j].st = time;
		printf("| %d %s ", jobs[j].st, jobs[j].name);
		time += jobs[j].tbt;
		jobs[j].ct = time;
		jobs[j].tat = jobs[j].ct - jobs[j].at;
		jobs[j].wt = jobs[j].tat - jobs[j].bt;
		printf("%d |", jobs[j].ct);
	}
	printf("\n");
}

// Function to print the output table
void print_output() 
{
	printf("\n\n");
	printf("\n---------------------------------------");
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
	take_input();
	sort();
	process();
	print_output();

	// Free the dynamically allocated memory
	free(jobs);

	return 0;
}