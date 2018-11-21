/*20153292 JeongHyeonjin*/

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFSIZE 256
#define QKEY (key_t)0111
struct msqq_data{
	long type;
	char text[BUFSIZE];
};

struct msqq_data send_data;
struct msqq_data recv_data;

int i=1;
int num=1;

void send();
void receive();

int main(){
	send_data.type=1;

	for(;;){
		send();
		printf("==========================================\n");

		if((i%2)!=0){
			num=1;
		}
		else{
			num=2;
		}
		receive();
	}
}

void send(){
	int qid,len;
	char buf[BUFSIZE];
	char *str;
	printf("%d send message : ",num);
	gets(send_data.text);
	i++;
	if((qid=msgget(QKEY,IPC_CREAT|0666))==-1){
		perror("msgget failed");
		exit(1);
	}
	if(msgsnd(qid,&send_data,strlen(send_data.text),0)==-1){
		perror("msgsnd failed");
		exit(1);
	}
}

void receive(){
	int qid,len;
	
	if((qid=msgget(QKEY,IPC_CREAT|0666))==-1){
		perror("msgrcv failed");
		exit(1);
	}
	if((len=msgrcv(qid,&recv_data,BUFSIZE,0,0))==-1){
		perror("msgrcv failed");
		exit(1);
	}
	printf("%d received message : %s\n",num,recv_data.text);
	if(msgctl(qid,IPC_RMID,0)==-1){
		perror("msgctl failed");
		exit(1);
	}
}
