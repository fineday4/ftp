#include "fun.h"

void puts_function(int new_fd,char* send_buf)
{
	char file[100] = "0";
	char* pstr = send_buf + 4;
	struct stat buf;
	strcpy(file,pstr);
	printf("puts_function get file:%s\n", file);
	int fd = open(file, O_RDONLY);
	if(-1 == fd)
	{
		sprintf(send_buf,"gets %s error,maybe this file not exsitent",file);
		return ;
	}
	int ret = fstat(fd, &buf);
	if(-1 == ret)
	{
		perror("fstat");
		return ;
	}
	int len;
	int file_len;
	file_len = buf.st_size;
	int send_size = 0;
	send(new_fd,(char*)&file_len,sizeof(int),0);
	while(1)
	{
		memset(send_buf,0,sizeof(send_buf));
		len = read(fd,send_buf,sizeof(send_buf));
		send_n(new_fd,(char*)&len,sizeof(len));
		if(len == 0)
		{
			printf("download success\n");
			send_n(new_fd,(char*)&len,sizeof(len));
			break;
		}
		send_n(new_fd,send_buf,len );
		send_size += len;
		printf("%8.2lf%s",100*(double)send_size/file_len,"%");
		fflush(stdout);
		printf("\r");
	}
	close(fd);
	return ;

}
