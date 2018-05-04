#include "fun.h"

void pwd_function(char* send_buf)
{
	char* str = (char*)malloc(1000*sizeof(char));
	str = getcwd(NULL,0);
	printf("pwd_function: %s\n", str);
	strcpy(send_buf,str);
	free(str);
}
