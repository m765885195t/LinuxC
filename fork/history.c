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

int main()
{
    int fd,i=0;
    char a,b[120];
    fd=open("/home/motian/linuxC/fork/h",O_RDONLY);
   
    while(read(fd,&a,1))
    {
        if(a!='\0')
        {
            
            if(a=='@')
            {
                a='\0';
                printf("%s\n",b);
                i=0;
            }
            else
            {
                b[i++]=a;
            }


        }
    }
}