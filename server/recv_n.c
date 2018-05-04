#include "fun.h"

void recv_n(int new_fd, char* recv_buf, int len)
{
	int total = 0;
	while(total < len)
	{
		total += recv(new_fd, recv_buf+total,len-total, 0);
	}
	return ;
}
