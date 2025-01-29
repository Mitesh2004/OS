#include<stdio.h>
#include<stdlib.h>
int main(){
	int i,j;
	int n,head,total_seek_time=0;

	// i/p no of disk requests
	printf("Enter no. of disk requests: ");
	scanf("%d",&n);
	int request[n];

	// i/p disk request queue
	printf("Enter disk request queue: ");
	for( i=0;i<n;i++){
		scanf("%d",&request[i]);
        }

	// i/p initial head pos
	printf("Enter initial head: ");
	scanf("%d",&head);

	//display seek sequnence
	printf("SEEK SEQUENCE: %d",head);
	for(i=0;i<n;i++){
		total_seek_time += abs(request[i]-head);
		head=request[i];
        	printf("->%d",head);
	}

	// o/p 
	printf("\n\ntotal seek time: %d\n",total_seek_time);
	printf("Average seek time: %.2f\n",(float)total_seek_time/n);

}


