/*20153292 JeongHyeonjin*/

#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

#define MSGSIZE 64
char *testfifo="fifo";

int main(int argc, char **argv){
	int fd,i,nwirte;
	char buf[MSGSIZE];
	
	if(argc<2){
		fprintf(stderr,"Usage: writefifo msg...\n");
		exit(1);
	}

	if((fd=open(testfifo, O_WRONLY))<0){
		perror("fifo open failed");
		exit(1);
	}

	for(i=1;i<argc;i++){
		strcpy(buf,argv[i]);
		if((nwirte=write(fd,buf,MSGSIZE))<0){
			perror("fifo write failed");
			exit(1);
		}
	}
}
