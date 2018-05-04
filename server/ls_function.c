#include "fun.h"

void ls_function(char* send_buf)
{
	struct dirent *pdirinfo;
	DIR *pdir;
	char* pstr = (char*)malloc(sizeof(char)*200);
	pstr = getcwd(NULL,0);
	pdir = opendir(pstr);
	if(NULL == pdir)
	{
		perror("opendir");
		return ;
	}
	while((pdirinfo = readdir(pdir)) != NULL)
	{
		strcat(send_buf,pdirinfo->d_name);
		strcat(send_buf,"	");
	}
	closedir(pdir);
}
