#include <stdio.h>
#include <termios.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>

void main(){
	time_t start=0,end=0;
	float gap=0;
	float tasu=1;
	int typing=0;
	int fd;
	int nread, cnt=0,errnt=0;
	
	char ch, text[]="The magic thing is that you can change it.";
	struct termios init_attr,new_attr;

	fd=open(ttyname(fileno(stdin)),O_RDWR);
	tcgetattr(fd,&init_attr);
	new_attr=init_attr;
	new_attr.c_lflag&=~ICANON;
	new_attr.c_lflag&=~ECHO;
	new_attr.c_cc[VMIN]=1;
	new_attr.c_cc[VTIME]=0;
	
	if(tcsetattr(fd,TCSANOW,&new_attr) != 0){
		fprintf(stderr,"TERMINOR NO SET.\n");
	}
	printf("write : \n%s\n",text);
	time(&start);
	while( (nread=read(fd,&ch,1)) >0 && ch!='\n'){
		//time(&start);
		if(ch==text[cnt++])
			write(fd,&ch,1);
		else{
			write(fd,"*",1);
			errnt++;
		}
		typing++;
	}
	time(&end);
	gap=end-start;
	float n=(float)(gap/60);
	tasu=(float)(typing/n);

	printf("\nerror count %d\n",errnt);
	printf("gap : %f\n",gap);
	printf("tasu : %f\n",tasu);
	tcsetattr(fd,TCSANOW,&init_attr);
	close(fd);
}
