/*20153292 JeongHyeonjin*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void sys(char *str[]){

	execl("/bin/ls",str[1],str[2],(char *)0);
	
}

int main(int argc, char *argv[]){

	sys(argv);

}
