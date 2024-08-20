/*#include<stdio.h>
#include<string.h>
#include<math.h>
struct job
{
char name[20];
int at,bt,ct,tat,wt,st,tbt;
}job[10];
int n,i,j;
float avg_tat=0; 
float avg_wt=0;
void take_input()
{
printf("Enter the no of jobs : ");
scanf("%d",&n);
for(i=0;i<n;i++)
{
printf("Enter the arrival time of the job",i);
scanf("%d",&job[i].at);
printf("Enter the bust time of the job",i);
scanf("%d",&job[i].bt);
printf("Enter the name of the job",i);
scanf("%s",&job[i].name);
job[i].tbt=job[i].bt;
printf("\n\n");
}
}
// to sort the processes by arriaval time
void sort()
{
struct job temp;
for(i=0;i<n;i++)
{
for(j=i+1;j<n;j++)
{
if(job[i].at>job[j].at)
{
temp=job[i];
job[i]=job[j];
job[j]=temp;
}
}
}
}
// to calculate the tat n wt
void process()
{
int time=job[0].at;
for(j=0;j<n;j++)
{
job[j].st=time;
printf("| %d %s ",job[j].st,job[j].name); 
time=time+job[j].tbt;
job[j].ct = time;
job[j].tat=time-job[j].at;
job[j].wt=job[j].tat-job[j].tbt;
printf("%d |",time);
}
}
//to print the output table
void print_output()
{
printf("\n\n");
printf("\n---------------------------------------");
printf("\n PName AT BT TAT WT ");
printf("\n---------------------------------------");
for(i=0;i<n;i++)
{
printf("\n%s %d %d %d %d",job[i].name,job[i].at,job[i].bt,job[i].tat,job[i].wt);
avg_tat=avg_tat+(float)(job[i].tat);
avg_wt=(float)avg_wt+(float)(job[i].wt);
}
printf("\n-----------------------------------------");
printf("\nTheavg of the Turn Around Time is %f",avg_tat/n);
printf("\nTheavg of the Waiting Time is %f",avg_wt/n);
}
int main()
{
	int i;
	take_input();
	sort();
	process();
	print_output();
	printf("\n\n");
	for(i=0;i<n;i++)
	{
		//job[i].tbt=job[i].bt=rand()%10+1;
		job[i].at=job[i].ct+2;
	} 
	process();
	print_output(); 
	*/

		/*
#include<stdio.h>
#include<string.h>
struct job 
{
char name[20];
int at, bt, ct, tat, wt, st, tbt;

} 
job[10];

int n, i, j;
float avg_tat = 0;
float avg_wt = 0;

void take_input() 
{
printf("Enter the number of jobs: ");
scanf("%d", &n);
for (i = 0; i < n; i++) 
{
printf("Enter the arrival time of job %d: ", i+1);
scanf("%d", &job[i].at);
printf("Enter the burst time of job %d: ", i+1);
scanf("%d", &job[i].bt);
printf("Enter the name of job %d: ", i+1);
scanf("%s", job[i].name);
job[i].tbt = job[i].bt;
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
	if (job[i].at > job[j].at) 
	{
	temp = job[i];
	job[i] = job[j];
	job[j] = temp;
	}
	}
	}
	}

	// Function to calculate the turnaround time and waiting time
	void process() 
	{
	int time = job[0].at;
	for (j = 0; j < n; j++) 
	{
	job[j].st = time;
	printf("| %d %s ", job[j].st, job[j].name);
	time += job[j].tbt;
	job[j].ct = time;
	job[j].tat = job[j].ct - job[j].at;
	job[j].wt = job[j].tat - job[j].bt;
	printf("%d |", job[j].ct);
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
		printf("\n%s      %d    %d    %d    %d", job[i].name, job[i].at, job[i].bt, job[i].tat, job[i].wt);
		avg_tat += job[i].tat;
		avg_wt += job[i].wt;
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
	return 0;
}
*/








#include <stdio.h>
#include <stdlib.h>  // Include for dynamic memory allocation

struct job 
{
    int at, bt, ct, tat, wt, st;
    char name[5];  // Name to hold "P0", "P1", ..., "Pn"
};

int n, i;
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
        printf("\n");
    }
}

// Function to sort the jobs by arrival time
void sort() 
{
    struct job temp;
    for (i = 0; i < n - 1; i++) 
    {
        for (int j = i + 1; j < n; j++) 
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
    int time = 0;  // Start time for processing
    for (i = 0; i < n; i++) 
    {
        if (time < jobs[i].at)
            time = jobs[i].at;  // Wait for the job to arrive if needed

        jobs[i].st = time;
        time += jobs[i].bt;
        jobs[i].ct = time;
        jobs[i].tat = jobs[i].ct - jobs[i].at;
        jobs[i].wt = jobs[i].tat - jobs[i].bt;
    }
}

// Function to print the Gantt chart and output table
void print_output() 
{
    int time = 0;
    for (i = 0; i < n; i++) 
    {
        if (jobs[i].ct > time)
            time = jobs[i].ct;
    }

    printf("\nGantt Chart:\n");
    printf("0");
    for (i = 0; i < n; i++) 
    {
        printf(" %d ", jobs[i].ct);
    }
    printf("\n");

    printf("|");
    for (i = 0; i < n; i++) 
    {
        printf(" %s ", jobs[i].name);
        if (i < n - 1) 
        {
            printf("|");
        }
    }
    printf("|\n");

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
