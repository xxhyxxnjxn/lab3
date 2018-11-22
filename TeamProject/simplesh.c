#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <termios.h>
#include <fcntl.h>

int getargs(char *cmd, char **argv);
void terminor();

int main(){
	char buf[256];
	char *argv[50];
	int narg;
	pid_t pid;
	//terminor();
	while(1){
		printf("shell > ");
		gets(buf);
		narg=getargs(buf,argv);
		pid=fork();
		if(pid==0){
			execvp(argv[0],argv);
			//perror("execvp");
			exit(0);
		}
		else if(pid>0){
			wait( (int *) 0);
			//printf("%s",buf);
			//exit(0);
		}
		else { 
			perror("fork failed");
		}
		
		if(strcmp(buf,"exit") == 0){
			exit(1);
		}
		if(strcmp(buf,"terminor")==0){
			terminor();
		}
	}
	return 0;
}
int getargs(char *cmd,char **argv){
	int nargs=0;
	while(*cmd){
		if(*cmd == '\t'||*cmd==' ')
			*cmd++='\0';
		else{
			argv[nargs++]=cmd++;
			while(*cmd!='\0'&& *cmd!='\t'&& *cmd!=' ')
				cmd++;
		}
	}
	argv[nargs]=NULL;

	return nargs;
}

void terminor(){
	int fd;
	struct termios init_attr, new_attr;
	fd=open(ttyname(fileno(stdin)),O_RDWR);
	tcgetattr(fd,&init_attr);
	new_attr=init_attr;
	new_attr.c_cc[VINTR]=3;
	new_attr.c_cc[VQUIT]=26;
	if(tcsetattr(fd,TCSANOW,&new_attr)!=0){
		fprintf(stderr,"Don't set\n");
	}
	close(fd);
}
