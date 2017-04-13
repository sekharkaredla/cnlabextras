#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>
#include<stdlib.h>
#include<arpa/inet.h>
#define SIZE 4
int main(int argc, char *argv[])
{
	int sfd,s,nsfd,len,i,j,status;
	char str[100],frame[100],temp[100],ack[20];
	struct sockaddr_in sa,ca;
	sfd=socket(AF_INET,SOCK_STREAM,0);
	//window size
	if(sfd<0)
	{
		perror("Error");
		exit(-1);
	}
	bzero(&sa,sizeof(sa));
	sa.sin_family=AF_INET;
	sa.sin_addr.s_addr=htonl(INADDR_ANY);
	sa.sin_port=htons(atoi(argv[1]));
	s=bind(sfd,(struct sockaddr*)&sa,sizeof(sa)); //assign a name to the server
	if(s<0)
	{
		perror("Bind Error");
		exit(-1);
	}
	listen(sfd,5);
	len=sizeof(&ca);
	nsfd=accept(sfd,(struct sockaddr*)&ca,&len); //take a connection request
	printf(" Enter the text : ");
	scanf("%s",&str);
	//read a string to be transmitted
	i=0;
	while(i<strlen(str))
	{
		memset(frame,0,100);
		strncpy(frame,str+i,SIZE);
		//generate a frame
		write(1," Transmitting Frames: ",23);
		len=strlen(frame);
		for(j=0;j<len;j++)
			//copy the sequence numbers into the frame
		{
			printf(" %d ",i+j);
			sprintf(temp," %d",i+j);
			strcat(frame,temp);
		}
		printf("\n");
		write(nsfd,&frame,sizeof(frame)); //send frames
		//printf("\nSent message: %s\n",frame);
		read(nsfd,ack,20);
		sscanf(ack,"%d",&status);
		if(status==-1)
			printf(" Transmission is successful. \n");
		else
		{
			printf(" Received error in frame: %d ",status);
			printf("\n Retransmitting Frames: ");
			for(j=0;;)
			{
				frame[j]=str[j+status];
				printf("%d ",j+status);
				j++;
				if((j+status)%4==0)
					break;
			}
			printf("\n");
			frame[j]='\0';
			len=strlen(frame);
			for(j=0;j<len;j++)
			{
				sprintf(temp," %d ",j+status);
				strcat(frame,temp);
			}
			write(nsfd,&frame,sizeof(frame)); //Retransmit the error frame
		}
		i+=SIZE;
	}
	write(nsfd,"exit",sizeof("exit"));
	printf("\nExiting.............\n");
	sleep(2);
	close(nsfd);
	close(sfd);
	return 0;
	//End of transmission
}
