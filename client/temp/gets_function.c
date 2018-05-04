#include "fun.h"

void gets_function(int sfd, char* send_buf)
{
	char file[1000] = {0};
	int  file_len = 0;
	char str_file_len[100] = {0};
	int ret;
	int len;
	char* pstr = send_buf+4;
	strcpy(file,pstr);
	int fd_file = open(file,O_CREAT|O_WRONLY,0666);
	if(-1 == fd_file)
	{
		perror("open fd_file");
		return ;
	}
	int fd_file_name = open(".file_name",O_CREAT|O_RDWR,0666);
	if(-1 == fd_file_name)
	{
		perror("open .file_name");
		return ;
	}
	char str_file_name[100] = {0};
	read(fd_file_name,str_file_name,sizeof(str_file_name));
	memset(file,0,sizeof(file));
	//获取文件大小
	//在获取文件大小之前需要先清空网络接收缓冲区
	int fd_temp1 = open(".file_size",O_CREAT|O_RDWR,0666);
	if(-1 == fd_temp1)
	{
		perror("open fd_tem1");
		return ;
	}
	len = read(fd_temp1,str_file_len,sizeof(file));
	file_len = atoi(str_file_len);
//	send(sfd,(char*)&file_len,sizeof(file_len),0);
	int write_len = 0;
	int fd_temp2 = open(".train",O_CREAT|O_RDWR,0666);
	if(-1 == fd_temp2)
	{
		perror("open3");
		return ;
	}				
	if(0 == file_len)
	{
		recv(sfd,(char*)&file_len,sizeof(int),0);
		printf("file_len get: %d\n", file_len);
		sprintf(file,"%d",file_len);
		write(fd_temp1,file,strlen(file));
	}else{
		//需要判断是否为同一个文件
		len = read(fd_temp2,file,sizeof(file));
		write_len = atoi(file);
		send(sfd,(char*)&write_len,sizeof(write_len),0);
		lseek(fd_file,SEEK_END,0);
	}
	struct epoll_event event, evs[2];
	memset(evs,0,sizeof(evs));
	int epfd = epoll_create(2);
	event.data.fd = sfd;
	event.events = EPOLLIN;
	epoll_ctl(epfd,EPOLL_CTL_ADD,sfd,&event);
	event.data.fd = 0;
	event.events = EPOLLIN;
	epoll_ctl(epfd,EPOLL_CTL_ADD,0,&event);
	int j;
	char prin[20];
	char str_write_len[100] = {0};
	printf("fsadfadsw");
	while(1)
	{
		printf("fsadfadsw");
		memset(file,0,sizeof(file));
		memset(prin,0,sizeof(prin));
		len = 0;
		ret = epoll_wait(epfd,evs,sfd+1,-1);
		for(j = 0; j < ret; j++)
		{
			if(evs[j].data.fd == sfd)
			{
				//接受len
				recv(sfd,(char*)&len,sizeof(len),0);
				if(file_len == write_len)
				{
					printf("Download success\n");
					break;
				}
				recv_n(sfd,file,len);
				write(fd_file,file,len);
				//在这里需要实现记录写入的字节信息
				write_len += len;
				printf("%8.2lf%s",100*(double)write_len/file_len,"%");
				fflush(stdout);
				printf("\r");
			}
			if(evs[j].data.fd == 0)
			{
				scanf("%s",prin);
				printf("you input:%s\n", prin);
				sprintf(str_write_len,"%d", write_len);
				write(fd_temp2,str_write_len,strlen(str_write_len));
				send(sfd,str_write_len,strlen(str_write_len),0);
				recv(sfd,file,sizeof(file), 0);
				printf("%s\n", file);
				close(fd_temp2);
				close(fd_file);
				close(fd_temp1);
				close(fd_file_name);
				break;
			}
		}
		if(write_len == file_len|strlen(prin) > 0)
		{
			break;
		}
	}
	close(fd_temp1);
	close(fd_file);
	return;
}
