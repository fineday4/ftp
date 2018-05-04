#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

int main()
{
	int fd = open("test",O_CREAT|O_WRONLY,0666);
	if(-1 == fd)
	{
		perror("open");
		return -1;
	}
	int len = 265432078;
	char buf[10];
	sprintf(buf,"%d",len);
	int ret = write(fd,&buf,strlen(buf));
	printf("ret = %d\n", ret);
	close(fd);
	return 0;
}
