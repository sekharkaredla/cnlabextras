#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "sys/types.h"
#include "sys/socket.h"
#include "arpa/inet.h"
#include "netinet/in.h"
#define SA struct sockaddr
struct IPmac {
char ip[100];
char mac[100];
};
int main() {
int sockfd,len,i;
struct sockaddr_in servaddr;
char buff[30],temp[30],ip[30],mac[30];
int flag=0;
struct IPmac in[3]={
{"10.1.1.8","44:dd:22:11:33"},
{"127.0.0.1","33:aa:fe:4e:2d"},
{"10.1.8.5","23:a3:5d:33:9d"}
};
//printing table
printf("ip\t\tmac\n");
for(i=0;i<3;i++)
{
printf("%s\t%s\n",in[i].ip,in[i].mac);
}
//create socket
sockfd = socket(AF_INET,SOCK_DGRAM,0);
//fill structure
servaddr.sin_family = AF_INET;
servaddr.sin_port = htons(9999);
servaddr.sin_addr.s_addr = INADDR_ANY;
//bind
bind(sockfd,(SA*)&servaddr,sizeof(servaddr));
//get ip from client
len=sizeof(servaddr);
recvfrom(sockfd,ip,sizeof(ip),0,(SA*)&servaddr,&len);
for(i=0;i<strlen(ip)-1;i++) {
temp[i]=ip[i];
}
temp[i]='\0';
printf("received IP :%s\n",temp);
//searching in table for equivalent mac
for(i=0;i<3;i++) {
if(strcmp(temp,in[i].ip)==0) {
strcpy(mac,in[i].mac);
break;
}
}
printf("mac address is %s\n",mac);
sendto(sockfd,mac,sizeof(mac),0,(SA*)&servaddr,len);
//rarp simulation
//recv mac address
bzero(mac,sizeof(mac));
recvfrom(sockfd,mac,sizeof(mac),0,(SA*)&servaddr,&len);
printf("received mac address :%s",mac);
//store in temp
bzero(temp,sizeof(temp));
for(i=0;i<strlen(mac)-1;i++) {
temp[i]=mac[i];
}
temp[i]='\0';
bzero(ip,sizeof(ip));
//check in table
for(i=0;i<3;i++) {
if(strcmp(temp,in[i].mac)==0) {
strcpy(ip,in[i].ip);
break;
}
}
printf("ip address :%s\n",ip);
sendto(sockfd,ip,sizeof(ip),0,(SA*)&servaddr,len);
return 0;
}
