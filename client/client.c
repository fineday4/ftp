#include "fun.h"
void user_pass(int sfd, char* recv_buf, char* send_buf )
{
	printf("Input user's name: ");
	scanf("%s", send_buf);
	int len = strlen(send_buf);
	send_n(sfd, (char*)&len, sizeof(len));
	send_n(sfd, send_buf,len);
	memset(send_buf,0,sizeof(send_buf));
	printf("Input your passwd:");
	scanf("%s", send_buf);
	len = strlen(send_buf);
	send_n(sfd,(char*)&len, sizeof(len));
	send_n(sfd,send_buf,len);
	return ;
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
	struct sockaddr_in ser;
	memset(&ser,0,sizeof(ser));
	ser.sin_family = AF_INET;
	ser.sin_addr.s_addr = inet_addr(argv[1]);
	ser.sin_port = htons(atoi(argv[2]));
	int len = sizeof(ser);
	int ret = connect(sfd,(struct sockaddr*)&ser,len);
	if(-1 == ret)
	{
		perror("connect");
		return -1;
	}
	printf("connect success\n");
	char send_buf[50] = "0";
	char recv_buf[2000] = "0";
	user_pass(sfd,recv_buf,send_buf);
	int flag = 1;
	int send_len = 0;
	while(1)
	{
		printf("->");
		scanf("%s",send_buf);
		printf("%s\n",send_buf);
		send_len = strlen(send_buf);
		send(sfd,(char*)&send_len,sizeof(int),0);
		send(sfd,send_buf,send_len,0);
		if(strncmp(send_buf,"gets",sizeof(char)*4) == 0)
		{
	//		len = atoi(recv_buf);
			gets_function(sfd,send_buf);
			printf("down here:59");
		}
		if(strncmp(send_buf,"puts",sizeof(char)*4) == 0)
		{
	//		len = atoi(recv_buf);
			puts_function(sfd,send_buf);
		}
		recv(sfd,recv_buf,sizeof(recv_buf),0);
		printf("down here:67");
		printf("client recv_buf:%s\n", recv_buf);
		if(strcmp(send_buf,"exit") == 0)
		{
			printf("exit success\n");
			break;
		}
		memset(send_buf,0,sizeof(send_buf));
		printf("recv_buf : %s\n", recv_buf);
		memset(recv_buf,0,sizeof(recv_buf));
	}
	printf("recv_buf : %s\n", recv_buf);
	close(sfd);
	return 0;
}
