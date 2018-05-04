#include "fun.h"

void gets_function(int new_fd,char* recv_buf,char* send_buf)
{
	char file[100] = "0";
	char* pstr = recv_buf + 4;
	struct stat buf;
	strcpy(file,pstr);
	printf("gets_function get file:%s\n", file);
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
	len = buf.st_size;
	send(new_fd,(char*)&len,sizeof(len),0);
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
	}
	close(fd);
	return ;

}
