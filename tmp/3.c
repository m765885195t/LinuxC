/*************************************************************************
	> File Name: 3.c
	> Author:motian 
	> Mail:765885195@qq.com 
	> Created Time: 2016年07月27日 星期三 21时04分17秒
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main()
{
    int i=0;
    pid_t pid;

    pid=vfork();
    
    if(pid==0)
        exit(0);
    printf("aa");
    return 0;
}
