#include "fun.h"

void puts_function(int sfd, char* recv_buf)
{
	char file[2000] = "0";
	int len = 0;
	int file_len = 0;
	int recv_file = 0;
	char* pstr = recv_buf + 4;
	strcpy(file,pstr);
	int fd = open(file,O_CREAT|O_WRONLY,0666);
	if(-1 == fd)
	{
		perror("open");
		return ;
	}
	recv_n(sfd,(char*)&file_len,sizeof(int));
	recv_n(sfd,(char*)&len,sizeof(len));
//	len = len - 1;
	printf("client gets_function recv_buf len: %s %d\n",recv_buf,len);
	while(len > 0)
	{
		memset(file,0,sizeof(file));
		recv_n(sfd,file,len);
		recv_file += len;
		printf("%8.2lf%s",100*(double)recv_file/file_len,"%");
		fflush(stdout);
		printf("\r");
		write(fd,file,len );
		recv_n(sfd,(char*)&len,sizeof(len));
	}
	close(fd);
	return ;
}
