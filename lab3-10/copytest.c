/*20153292 JeongHyeonjin*/

#include <sys/types.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#define SHMSIZE 1024
#define SHMKEY (key_t)0111
#define SEMKEY (key_t)0111

//void testsem(int semid);
void testcopy(char *src[],int semid);
void testread();

void p(int semid);
void v(int semid);

mode_t mode = S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH;

int main(int argc,char *argv[]){
	int semid,i;
	pid_t pid;
	union semun{
		int value;
		struct semid_ds *buf;
		unsigned short int *array;
	}arg;

	if((semid=semget(SEMKEY,1,IPC_CREAT|0666))==-1){
		perror("segmget failed");
		exit(1);
	}
	arg.value=1;	
	if(argc<3){
		fprintf(stderr,"Usage:file_copy src_file dest_file\n");
		exit(1);
	}
	if(semctl(semid,0,SETVAL,arg)==-1){
		perror("semctl failed");
		exit(1);
	}
	pid=fork();
	if(pid==0){
		testcopy(argv,semid);
	}
	testread();
	if(semctl(semid,0,IPC_RMID,arg)==-1){
		perror("semctl failed");
		exit(1);
	}

}
void testcopy(char *src[],int semid){
	int src_fd;
	int shmid,len;
	void *shmaddr;
	p(semid);
	if((shmid=shmget(SHMKEY,SHMSIZE,IPC_CREAT|0666))==-1){
		perror("shmget failed");
		exit(1);
	}
	if((shmaddr=shmat(shmid,NULL,0))==(void *)-1){
		perror("shmat failed");
		exit(1);
	}
	if( (src_fd=open(src[1],O_RDONLY))==-1){
		perror("file open");
		exit(1);
	}
	strcpy((char *)shmaddr,src[2]);
	if(shmdt(shmaddr)==-1){
		perror("shmdt failed");
		exit(1);
	}

	close(src_fd);
	v(semid);
}
void testread(){
	int dst_fd;
	int shmid,len;
	void *shmaddr;

	if((shmid=shmget(SHMKEY,SHMSIZE,IPC_CREAT|0666))==-1){
		perror("shmget failed");
		exit(1);
	}
	if((shmaddr=shmat(shmid,NULL,0))==(void *)-1){
		perror("shmat failed");
		exit(1);
	}
	if((shmaddr=shmat(shmid,NULL,0))==(void *)-1){
		perror("shmat failed");
		exit(1);
	}
	if((dst_fd=creat((char *)shmaddr,mode))==-1){
		exit(1);
	}
	if(shmdt(shmaddr)==-1){
		perror("shmdt failed");
		exit(1);
	}
	if(shmctl(shmid,IPC_RMID,0)==-1){
		perror("shmctl failed");
		exit(1);
	}
}
void p(int semid){
	struct sembuf pbuf;
	pbuf.sem_num=0;
	pbuf.sem_op=-1;
	pbuf.sem_flg=SEM_UNDO;
	if(semop(semid,&pbuf,1)==-1){
		perror("semop failed");
		exit(1);
	}
}
void v(int semid){
	struct sembuf vbuf;
	vbuf.sem_num=0;
	vbuf.sem_op=1;
	vbuf.sem_flg=SEM_UNDO;
	if(semop(semid,&vbuf,1)==-1){
		perror("semop failed");
		exit(1);
	}
}
