#include "fun.h"

void cd_function(char* recv_buf, char* send_buf)
{
	char dir[50] = "0";	
	char* pstr = recv_buf + 2;
	strcpy(dir,pstr);
	int ret = chdir(dir);
	if(-1 == ret)
	{
		strcpy(send_buf,"not has this dir");
		return ;
	}
	strcpy(send_buf,"cd-success");
	return ;
}
