#include<stdio.h>
#include <netinet/in.h>
int main()
{
	short s=0x56AB;
	printf("value in deciaml:%d\n",s);
	printf("big endian:%x\n",htons(s));
	printf("little endian:%x\n",ntohs(htons(s)));
	printf("final value : %d\n",ntohs(htons(s)));
}
