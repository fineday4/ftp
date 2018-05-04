#include "fun.h"

//服务器端：step1:(目的：文件定位)接收客户端发过来的标记(flag)
//flag == 0:表示这是首次传送，故不需要获取上一次传送的字符数量，
//flag == 1:表示这不是首次传送，故需要获取上次传送了多少字符，并且
//从传送的文件中定位
//step2:（目的：文件传送）传送文件，同时无阻塞接收客户端可能发来的字符；
//step3:（目的：停止传送）当接收到客户端发来的消息时，停止发送字符，跳出循环，
//结束进程;
//需要创建一个记录下载文件的文档，用于记录没有一次性下载完成的文件的名字。
void gets_function(int new_fd, char* recv_buf, char* send_buf)
{
	char file[100] = {0};  //记录文件名和传送字符串
	int file_len;  //记录文件总长度
	struct stat buf;  //记录文件信息
	int ret;
	int len;    //记录每次传送的字符串的长度
	int train_len = 0;   //记录传输了多少字符
	int tap_train_len = 0; //记录是否出现断点
	char str_tap_train_len[100] = {0};
	char str_train_len[100] = {0};   //将断点写入.train文件中.
	char flag[100] = {0};
    recv(new_fd,str_train_len,sizeof(str_train_len),MSG_DONTWAIT);
	tap_train_len = atoi(str_train_len);
	char* pstr = recv_buf + 4;
	strcpy(file,pstr);
	int fd = open(file,O_RDONLY);
	if(-1 == fd)
	{
		perror("open");
		return ;
	}
	//方案一：通过一个文件来记录传送的字符
	//这个方案不可行，应为客户端和服务器端记录传送的字符的数量
	//并不相同。
	int fd_train = open(".train",O_CREAT|O_RDWR,0666);
	if(-1 == fd_train)
	{
		perror(".train open error");
		return ;
	}
	char test_buf[100] = {0};
	ret = read(fd_train,test_buf,sizeof(test_buf));
	if(0 == ret)
	{
		ret = write(fd_train,file,strlen(file));
		if(0 == ret)
		{
			perror("write");
			return ;
		}
		fstat(fd,&buf);
		file_len = buf.st_size;
		printf("file_len: %d\n", file_len);
		send(new_fd,(char*)&file_len,sizeof(int),0);
	}else{
		if(strcmp(test_buf,file) == 0)
		{
			recv(new_fd,str_train_len,sizeof(str_train_len),0);
			train_len = atoi(str_train_len);
			lseek(fd,SEEK_SET,train_len);
		}
	}
	while(1)
	{
		ret = 0;
		memset(file,0,sizeof(file));
		len = read(fd,file,sizeof(file));
		if(file_len == train_len)
		{
			len = 0;
			send_n(new_fd,(char*)&len,sizeof(len));
			//删除掉.train文件
			break;
		}
		send_n(new_fd, (char*)&len,sizeof(len));
		send_n(new_fd,file,len);
		train_len += len;
		//循环就阻塞在了recv函数上了。
		ret = recv(new_fd,flag,sizeof(flag),MSG_DONTWAIT);
		if(ret > 0)
		{
			printf("had trainscent: %s\n", flag);
			//在这里实现存储断点到文件中，以便于下次继续上传。
//			sprintf(str_train_len,"%d", train_len);
//			write(fd_train,str_train_len,strlen(str_train_len));
//			close(fd_train);
			break;
		}
	}
	return ;
}
