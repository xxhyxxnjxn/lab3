#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

const char *endstring=".";

int main(int argc,char *argv[]){
	int fd;
	off_t size;
	off_t hole_size;

	if(argc<2){
		fprintf(stderr,"Usage: file_size filename\n");
		exit(1);
	}

	if( (fd=open(argv[1],O_RDWR))==-1){
		perror("open");
		exit(1);
	}
	
	hole_size=atoi(argv[2]);

	size=lseek(fd,0,SEEK_END);
	printf("Before : %s\'s size = %d\n",argv[1],size);

	lseek(fd,hole_size,SEEK_END);
	write(fd, endstring, 1);
	
	size=lseek(fd,0,SEEK_END);
	printf("After : %s\'s size = %d\n",argv[1],size);

	close(fd);
	
}
