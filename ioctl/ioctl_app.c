#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <errno.h> 
#define WR_VALUE _IOW('a','a',int32_t*)
#define RD_VALUE _IOR('a','b',int32_t*)
int main()
{
		int fd;
        printf("\nOpening Driver\n");
        fd = open("/dev/dummy", O_RDWR);
        printf("file descriptor:%d\n",fd );
        if(fd < 0) 
        {
                printf("Cannot open device file...\n");
                return 0;
        }
 
      

        if(ioctl(fd,1,NULL)<0)
        {
        	printf("ioctl: %s\n", strerror(errno));
        	return -1;
        }

        printf("ioctl success\n");
        return 0;
}
