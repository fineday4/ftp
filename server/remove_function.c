#include "fun.h"

void remove_function(char* recv_buf,char* send_buf)
{
	char pstr[200] = "0";
	char* psend = recv_buf + 6;
	strcpy(pstr,psend);
	printf("remove_function: %s\n", pstr);
	int ret = remove(pstr);
	if(-1 == ret)
	{
		strcpy(send_buf,"remove error");
		return ;
	}
	strcpy(send_buf,"remove - function");
}
