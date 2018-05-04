#include "fun.h"

void send_n(int new_fd, char* send_buf, int len)
{
	int total = 0;
	while(total < len)
	{
		total += send(new_fd, send_buf + total, len - total,0 );
	}
	return ;
}
