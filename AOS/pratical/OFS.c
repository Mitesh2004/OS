#include<stdio.h>
#include<unistd.h>
#include<fcntl.h> 
#include<sys/types.h>
int main(){
	int fd;
	char lilbuf[20],bigbuf[1024];
	fd = open("a.out",O_RDONLY);
	printf("File open");
	read(fd,lilbuf,20);
	read(fd,bigbuf,1024);
}






