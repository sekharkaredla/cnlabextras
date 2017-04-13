#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
void main()
{
execlp("/usr/bin/python","python","rsanew.py",NULL);
}
