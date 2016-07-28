/*************************************************************************
	> File Name: 2.c
	> Author:motian 
	> Mail:765885195@qq.com 
	> Created Time: 2016年07月27日 星期三 19时46分49秒
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int t()
{
    char a[1024];
    pid_t pid;
    
        pid=fork();
    if(pid>0)
    {

    }
    if(pid==0)
    {
        puts("sss");
        exit(0);
    }

}

int main(void)
{
    while(1)
    {

        printf("motian:\n");
        t();

    }
}
