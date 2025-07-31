#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h>
int main(int argc, char *argv[]){ if(argc != 2){ printf("Usage: %s <fn>\n",argv[0]); return 1;}
	const char *fn = argv[1];
	if(access(fn, F_OK)==0){printf("File '%s' exists in the current directory.\n",argv[1]);}
	else{printf("File '%s' doesn't exist in the current directory.\n",fn);}
	return 0;
}
