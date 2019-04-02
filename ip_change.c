#include <stdio.h>
#include <unistd.h>
#include <string.h> /* for strncpy */

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>

int
main()
{
 int fd;
 struct ifreq ifr;
 char a[200];
 
 fd = socket(AF_INET, SOCK_DGRAM, 0);
 ifr.ifr_addr.sa_family = AF_INET;
 strncpy(ifr.ifr_name, "wlp2s0", IFNAMSIZ-1);

 ioctl(fd, SIOCGIFADDR, &ifr);

 close(fd);

 
 printf("%s\n", inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr));


 unsigned char ip_address[15];
 
    struct sockaddr_in *addr;
     
    /*Read IP Address*/
    printf("Enter Ip Address: ");
    scanf("%s",ip_address);
     
    fd = socket(AF_INET, SOCK_DGRAM, 0);
     
    ifr.ifr_addr.sa_family = AF_INET;
     
     memcpy(ifr.ifr_name, "wlp2s0", IFNAMSIZ-1);
     
    addr=(struct sockaddr_in *)&ifr.ifr_addr;
     
    
    inet_pton(AF_INET,ip_address,&addr->sin_addr);
     
    /*Setting the Ip Address using ioctl*/
    ioctl(fd, SIOCSIFADDR, &ifr);
    /*closing fd*/
    close(fd);
     
    printf("IP Address updated sucessfully.\n");
   
    memset((unsigned char*)ip_address,0x20,15);
    ioctl(fd, SIOCGIFADDR, &ifr);
    /*Extracting Ip Address*/
    strcpy(ip_address,inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr));
     
    printf("Updated IP Address is: %s\n",ip_address);



 return 0;

}