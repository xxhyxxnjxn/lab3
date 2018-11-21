/*20153292 JeongHyeonjin*/

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFSIZE 16
#define QKEY (key_t)0111
struct msqq_data{
	long type;
	char text[BUFSIZE];
};

struct msqq_data send_data;

int main(){
	send_data.type=1;

	int qid,len;
	char buf[BUFSIZE];
	char str[100];

	printf("send message : ");
	//scanf("%s",send_data.text);
	gets(send_data.text);

	if((qid=msgget(QKEY,IPC_CREAT|0666))==-1){
		perror("msgget failed");
		exit(1);
	}

	if(msgsnd(qid,&send_data,strlen(send_data.text),0)==-1){
		perror("msgsnd failed");
		exit(1);
	}
}

