#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "sys/types.h"
#include "sys/socket.h"
#include "arpa/inet.h"
#include "netinet/in.h"
#define SA struct sockaddr
int main() 
{
int sockfd,len;
char ip[30],mac[30];
struct sockaddr_in servaddr;
//creating socket
sockfd = socket(AF_INET,SOCK_DGRAM,0);
//fill structure
servaddr.sin_family = AF_INET;
servaddr.sin_port = htons(9999);
servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
//send ip address
printf("ARP SIMULATION\n");
printf("enter ip address :");
fgets(ip,sizeof(ip),stdin);
sendto(sockfd,ip,sizeof(ip),0,(SA*)&servaddr,sizeof(servaddr));
len=sizeof(servaddr);
recvfrom(sockfd,mac,sizeof(mac),0,(SA*)&servaddr,&len);
printf("MAC address is: %s\n",mac);
printf("RARP simulation\n");
printf("enter mac address :");
bzero(mac,sizeof(mac));
fgets(mac,sizeof(mac),stdin);
sendto(sockfd,mac,sizeof(mac),0,(SA*)&servaddr,len);
recvfrom(sockfd,ip,sizeof(ip),0,(SA*)&servaddr,&len);
printf("IP address is: %s\n",ip);
return 0;
}
