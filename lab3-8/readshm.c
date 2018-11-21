/*20153292 JeongHyeonjin*/

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#define SHMSIZE 1024
#define SHMKEY (key_t)0111

int main(){
	int shmid, len;
	void *shmaddr;

	if((shmid=shmget(SHMKEY, SHMSIZE, IPC_CREAT|0666))==-1){
		perror("shmget failed");
		exit(1);
	}
	if((shmaddr=shmat(shmid, NULL, 0))==(void *)-1){
		perror("shmat failed");
		exit(1);
	}
	if((shmaddr=shmat(shmid,NULL,0))==(void *)-1){
		perror("shmat failed");
		exit(1);
	}
	printf("received from shared memory: %s\n",(char *)shmaddr);

	if(shmdt(shmaddr)==-1){
		perror("shmdt failed");
		exit(1);
	}
	if(shmctl(shmid,IPC_RMID,0)==-1){
		perror("shmctl failed");
		exit(1);
	}
}
