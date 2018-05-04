#include "fun.h"

void gets_function(int sfd, char* send_buf)
{
	char file_name[100] = {0};
	char* pstr = send_buf + 4;
	strcpy(file_name, pstr);
	int fd_file = open(file_name,O_CREAT|O_WRONLY,0666);
	int fd_file_name = open(".file_name", O_CREAT|O_RDWR,0666);
	int fd_file_size = open(".file_size", O_CREAT|O_RDWR,0666);
	int fd_file_train = open(".file_train", O_CREAT|O_RDWR,0666);
	char read_file_name[100] = {0};
	char read_file_train[100] = {0};
	int file_train = 0;
	int file_size = 0;
	char str_file_size[100] = {0};
	char str_file_train[100] = {0};
	int ret = read(fd_file_name,read_file_name,sizeof(read_file_name));
	int flag = 0;
	if(ret > 0)
	{
		read(fd_file_train,read_file_train,sizeof(read_file_train));
		printf("if ret > 0 read file_train: %s\n", read_file_train);
		send(sfd,read_file_train,strlen(read_file_train),0);
		printf("send read_file_train success\n");
		file_train = atoi(read_file_train);
		printf("read_file_train to file_train: %d\n", file_train);
		lseek(fd_file,0,SEEK_END);
		read(fd_file_size,str_file_size,sizeof(str_file_size));
		file_size = atoi(str_file_size);
		printf("if success\n");
		flag = 1;
	}else{
		write(fd_file_name,file_name,strlen(file_name));
		recv_n(sfd,(char*)&file_size,sizeof(file_size));
		sprintf(str_file_size,"%d",file_size);
		write(fd_file_size,str_file_size,strlen(str_file_size));
		printf("else success\n");
	}
	close(fd_file_size);
	close(fd_file_name);
	int len = 0;
	struct epoll_event event, evs[2];
	int epfd = epoll_create(2);
	event.events = EPOLLIN;
	event.data.fd = sfd;
	if(-1 == epoll_ctl(epfd,EPOLL_CTL_ADD,sfd,&event))
	{
		perror("epoll_ctl_add: sfd");
		return ;
	}
	event.events = EPOLLIN;
	event.data.fd = 0;
	if(-1 == epoll_ctl(epfd,EPOLL_CTL_ADD,0,&event))
	{
		perror("epoll_ctl_add: 0");
		return ;
	}
	int i;
	char buf[20] = {0};
	char junk[100] = {0};
	printf("没有进入循环\n");
	//客户端
	while(1)
	{
		//客户端监听网络和输入
		ret = epoll_wait(epfd,evs,sfd+1,-1);
		memset(send_buf,0,sizeof(send_buf));
		for(i = 0; i < ret; i++)
		{
			//如果网络有消息
			if(evs[i].data.fd == sfd)
			{
				len = 0;
				//接收下一次要传送的字符的数量len
				recv(sfd,(char*)&len,sizeof(len),0);
				if(flag&&len > 1000)
				{
					printf("recv len: %d\n", len);
					break;
				}
				//如果接收的len == 0则表示下载完成
				if(0 == len)
				{	
					printf("Download success\n");
					break;
				}
				//接收len长的字符串
				recv_n(sfd,send_buf,len);
				//将len长的字符串写入fd_file文件中
				write(fd_file,send_buf,len);
				//file_train记录一共传送了多少字符到fd_file文件中了。
				file_train += len;
				printf("Dowload: %8.2lf%s", 100*(double)file_train/file_size,"%");
				fflush(stdout);
				printf("\r");
			}
			if(evs[i].data.fd == 0)
			{
				scanf("%s", buf);
				printf("%s\n",buf);
				send(sfd,&file_train,sizeof(int),0);
				sprintf(str_file_train,"%d", file_train);
				printf("str_file_train: %s\n", str_file_train);
				write(fd_file_train,str_file_train,strlen(str_file_train));
				recv(sfd,junk,sizeof(junk),MSG_DONTWAIT);
				break;
			}
		}
		if(0 == len|strlen(buf) > 0|len > 1000)
		{
			break;
		}
	}
	close(fd_file_train);
	close(fd_file);
	return ;
}
