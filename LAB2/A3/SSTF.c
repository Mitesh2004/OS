#include<stdio.h>
#include<stdlib.h>

#define MIN 999999

int main(){
	int i,j;
	int n,head,total_seek_time=0,temp, min_seek, min_idx;

	// i/p no of disk requests
	printf("Enter no. of disk requests: ");
	scanf("%d",&n);
	int request[n],visited[n];

	// i/p disk request queue
	printf("Enter disk request queue: ");
	for( i=0;i<n;i++){
		scanf("%d",&request[i]);
		visited[i]=0; //initial
	}

	// i/p initial head pos
	printf("Enter initial head: ");
	scanf("%d",&head);

	//display seek sequnence
	printf("SEEK SEQUENCE: %d",head);
	for(i=0;i<n;i++){
		//find closest unvisited request
          	min_seek=MIN;
		for(j=0;j<n;j++){
			if(visited[j]==0){
				temp=abs(request[j]-head);
				if(temp <min_seek){
					min_seek=temp;
					min_idx=j;
				}
			}
		}
		total_seek_time += min_seek;
		head=request[min_idx];
		visited[min_idx]=1;
		printf("->%d",head);
	}

	// o/p 
	printf("\n\ntotal seek time: %d\n",total_seek_time);
	printf("Average seek time: %.2f\n",(float)total_seek_time/n);

}

