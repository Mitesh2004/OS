#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
int main(){
	int file=open("op.txt",O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if(file==-1){perror("Error");
		return 1;
	}
	int saved_stdout=dup(fileno(stdout));
	if(dup2(file, fileno(stdout)) == -1){
		perror("Error");
		close(file);
		return 1;
	}
	printf("This is redirected standard op using dup and open system call\n");
	close(file);
	dup2(saved_stdout, fileno(stdout));
	close(saved_stdout);
	return 0;
}
