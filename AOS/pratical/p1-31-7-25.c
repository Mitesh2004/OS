#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
int main(){
	int pipe_fd[2];
	pid_t child_pid;
	if(pipe(pipe_fd)== -1){ 
		perror("Error creating pipe");
		exit(EXIT_FAILURE);
	}
	if((child_pid = fork())== -1){perror("Error");}

	if(child_pid == 0){
		close(pipe_fd[1]);
		dup2(pipe_fd[0],STDIN_FILENO);
		close(pipe_fd[0]);
		execlp("wc","wc","-l",(char *)NULL);
		perror("Error executing wc");
		exit(EXIT_FAILURE);
	}else{  close(pipe_fd[0]);
		dup2(pipe_fd[1],STDIN_FILENO);
		close(pipe_fd[1]);
		execlp("ls","ls","-l",(char *)NULL);
		perror("Error executing Is");
		exit(EXIT_FAILURE);
	}
	wait(NULL);
	return 0;
}
