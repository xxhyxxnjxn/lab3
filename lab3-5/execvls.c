/*20153292 JeongHyeonjin*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
	char * const argv[]={"ls","-al",(char *)0};
	printf("executing execv.\n");
	execv("/bin/ls",argv);
	perror("execv failed to run ls");
	exit(1);
}
