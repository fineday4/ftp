#include "fun.h"

void gets_function(int new_fd, char* recv_buf, char* send_buf)
{
	char file_name[100] = {0};
	char* pstr = recv_buf + 4;
	strcpy(file_name, pstr);
	int fd_file = open(file_name,O_RDONLY);
	int fd_file_name = open(".file_name",O_CREAT|O_RDWR,0666);
	char str_file_name[100] = {0};
	int ret = read(fd_file_name,str_file_name,sizeof(str_file_name));
	int file_train = 0;
	struct stat buf;
	fstat(fd_file,&buf);
	int file_len = buf.st_size;
	char str_file_train[100] = {0};
	int flag = 0;
	if(ret > 0)
	{
		flag = 1;
		printf("go into if ret > 0");
		recv(new_fd,str_file_train,sizeof(str_file_train),0);
		file_train = atoi(str_file_train);
		printf("if success: %d\n", file_train);
		ret = lseek(fd_file,file_train,SEEK_SET);
		if(-1 == ret)
		{
			perror("lseek");
			return;
		}
		printf("lseek sucess\n");
	}else{
		send_n(new_fd,(char*)&file_len,sizeof(file_len));
		write(fd_file_name,file_name,strlen(file_name));
		close(fd_file_name);
		printf("else success\n");
	}
	//上文已经给出了传送了多少字符
	int len = 0;
	char str_buf[20] = {0};
	file_train = 0;
	//服务器端
	while(1)
	{
		ret = 0;
		memset(send_buf,0,sizeof(send_buf));
		//len表示从文件中读取的字符数
		len = read(fd_file,send_buf,sizeof(send_buf));
		if(flag)
		{
			printf("read len: %d\n", len);
		}
		//将读取的字符数发送到客户端
		send_n(new_fd,(char*)&len,sizeof(len));
		if(flag)
		{
			printf("send len: %d\n", len);
		}
		if(len == 0)
		{
			printf("Download success\n");
			break;
		}
		//将读取的字符串发送到客户端
		send_n(new_fd,send_buf,len);
		//随时接收来自客户端的结束下载的请求
		recv(new_fd,(char*)&file_train,sizeof(int),MSG_DONTWAIT);
		//如果接收到客户端发来的请求则跳出循环
		if(file_train > 0)
		{
			printf("%d\n", file_train);
			break;
		}
	}
	printf("while break\n");
	send(new_fd,"success",7,0);
	close(fd_file);
	return ;
}
