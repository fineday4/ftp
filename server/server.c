#include "fun.h"

void get_salt(char* salt, char* passwd)
{
	int i, j;
	for(i = 0, j = 0; passwd[i]&&j != 3; ++i)
	{
		if(passwd[i] == '$')
		{
			++j;
		}
	}
	strncpy(salt,passwd,i-1);
}
int user_pass(int new_fd, char* recv_buf)
{
	struct spwd* sp;
	int len;
	char salt[512] = {0};
	char name[30] = {0};
	char passwd[30] = {0};
	recv_n(new_fd, (char*)&len,sizeof(len));
	recv_n(new_fd,name,len);
	strcpy(recv_buf,name);
	int fd = open(name,O_CREAT|O_WRONLY,0666);
	if(-1 == fd)
	{
		perror("open");
		return -1;
	}
	printf("server get username: %s\n", name);
	recv_n(new_fd, (char*)&len,sizeof(len));
	recv_n(new_fd, passwd,len);
	printf("server get passwd: %s\n", passwd);
	if((sp = getspnam(name)) == NULL)
	{
		printf("username error\n");
		return -1;
	}
	get_salt(salt,sp->sp_pwdp);
	if(strcmp(sp->sp_pwdp,crypt(passwd,salt)) == 0)
	{
		write(fd,name,strlen(name));
		write(fd,"\n",sizeof(char));
//		lseek(fd,0,SEEK_END);
		printf("Load success!\n");
		return 0;
	}else{
		printf("Load fail\n");
		return -1;
	}
}
int main(int argc, char** argv)
{
	if(argc != 3)
	{
		printf("Input IP and Port\n");		return -1;
	}
	int sfd = socket(AF_INET,SOCK_STREAM,0);
	if(-1 == sfd)
	{
		perror("socket");
		return -1;
	}
	time_t t;
	struct sockaddr_in ser;
	memset(&ser,0,sizeof(ser));
	ser.sin_family = AF_INET;
	ser.sin_addr.s_addr = inet_addr(argv[1]);
	ser.sin_port = htons(atoi(argv[2]));
	int len = sizeof(ser);
	int flag;
	int ret = bind(sfd,(struct sockaddr*)&ser,len);
	if(-1 == ret)
	{
		perror("bind");
		return -1;
	}
	listen(sfd,10);
	char* send_buf = (char*)malloc(1000*sizeof(char));
	int new_fd;
	char recv_buf[50] = "0";
	int fd = -1;
	int recv_len = 0;
	while(1)
	{
		new_fd = accept(sfd,(struct sockaddr*)&ser,&len);
		if(-1 == new_fd)
		{
			perror("accept");
			return -1;
		}
		printf("accept success\n");
		flag = user_pass(new_fd, recv_buf);
		if(flag == 0)
		{
			fd = open(recv_buf,O_WRONLY);
			if(-1 == fd)
			{
				perror("open");
				return -1;
			}
			memset(recv_buf,0,sizeof(recv_buf));
		}
		while(1)
		{
			if(flag == -1)
			{
				strcpy(send_buf,"Load fail");
				send_n(new_fd,send_buf,sizeof(send_buf));
				break;
			}
			recv(new_fd,(char*)&recv_len,sizeof(int),0);
			recv(new_fd,recv_buf,recv_len,0);
			t = time(NULL);
			gmtime(&t);
			lseek(fd,0,SEEK_END);
			write(fd,ctime(&t),strlen(ctime(&t)));
			write(fd,"\n",sizeof(char));
			write(fd,recv_buf,strlen(recv_buf));
			write(fd,"\n",sizeof(char));
			printf("client_send_buf: %s\n", recv_buf);
			function(new_fd,recv_buf, send_buf);
			if(strcmp(send_buf,"error") == 0)
			{
				printf("execute error function has a problem\n");
			}
			if(strcmp(recv_buf,"exit") == 0)
			{
				printf("client exit success!\n");
				memset(recv_buf,0,sizeof(recv_buf));
				memset(send_buf,0,sizeof(send_buf));
				close(fd);
				break;
			}
			memset(recv_buf,0,sizeof(recv_buf));
			send(new_fd,send_buf,strlen(send_buf),0);
			memset(send_buf,0,sizeof(send_buf));
		}
		printf("exit %d success\n", new_fd);
		close(new_fd);
	}
	close(sfd);
	free(send_buf);
	return 0;
}
