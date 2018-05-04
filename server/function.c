#include "fun.h"

void function(int new_fd,char* recv_buf, char* send_buf)
{
	printf("function get recv_buf: %s\n", recv_buf);
	char str[50] = "0";
	strcpy(str,recv_buf);
	if(strcmp(str,"ls") == 0)
	{
		ls_function(send_buf);
	}else if(strncmp(str,"cd",sizeof(char)*2) == 0){
		printf("function: %s\n", str);
		cd_function(recv_buf,send_buf);
	}else if(strncmp(str, "puts",sizeof(char)*4) == 0)
	{
		puts_function(new_fd,recv_buf);
	}else if(strncmp(str,"gets",sizeof(char)*4) == 0)
	{
		gets_function(new_fd,recv_buf,send_buf);
		printf("down: 20\n");
	}else if(strncmp(str,"remove",sizeof(char)*6) == 0)
	{
		 remove_function(recv_buf,send_buf);
	}else if(strcmp(str,"pwd") == 0)
	{
		 pwd_function(send_buf);
	}else{
		error(send_buf);
	}
	return ;
}
