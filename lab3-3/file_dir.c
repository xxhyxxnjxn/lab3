#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

#define MAX_BUF 256
void subdir(char *wd);

void main(int argc,char *argv[]){
	
	char buf [MAX_BUF];
	
	DIR *pdir;
	struct dirent *pde;
	int i=0;
	char *strbuf;

	if(argc<2){
		fprintf(stderr,"Usage:file_dir dirname\n");
		exit(1);
	}
	subdir(argv[1]);

}
void subdir(char *wd){
	char buf [MAX_BUF];

	DIR *pdir;
	struct dirent *pde;
	struct stat fstat;
	int i=0;
	int count=0;
	char *str;
	
	if(chdir(wd)<0){
		perror("chdir");
		exit(1);
	}
	
	memset(buf,0,MAX_BUF);
	if(getcwd(buf,MAX_BUF)<0){
		perror("getcwd");
		exit(1);
	}
	//printf("%s : \n",buf);

	if ( (pdir=opendir("."))<0){
		perror("opendir");
		exit(1);
	}
	while( (pde=readdir(pdir))!=NULL){
		if( (!strcmp(pde->d_name,"."))|| (!strcmp(pde->d_name,"..")))
			continue;
		printf("%s \n",pde->d_name);
		stat(pde->d_name,&fstat);
		if(S_ISDIR(fstat.st_mode)){
			subdir(pde->d_name);
			//if directory, Recursive visit
		}
	}
	closedir(pdir);
	chdir("..");
}
