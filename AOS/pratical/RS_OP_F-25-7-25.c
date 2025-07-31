#include<stdio.h>
int main(){
	FILE * file=freopen("op.txt","w",stdout);
	if(file==NULL){
		perror("Error opening file"); 
		return 1;
	}
	printf("This is redirected standard o/p.\n");
	fclose(file);
	return 0;
}

