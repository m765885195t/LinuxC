/*************************************************************************
	> File Name: history.c
	> Author:motian 
	> Mail:765885195@qq.com 
	> Created Time: 2016年07月28日 星期四 15时29分21秒
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>

int main()
{
    int fd,i=0,len;
    char *p,a[120];
    fd=open("/home/motian/linuxC/fork/h",O_RDONLY);

    read(fd,&a,120);
    
    len=strlen(a);
    
    p=a;

    for(i=0;i<len;i++)
    {
        if(a[i]=='+')
        {
            a[i]='\0';
            printf("%s\n",p);
            p=a+i+1;
        }
    }
}
