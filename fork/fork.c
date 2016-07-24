/*************************************************************************
	> File Name: fork.c
	> Author:motian 
	> Mail:765885195@qq.com 
	> Created Time: 2016年07月23日 星期六 14时44分25秒
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
int main(void)
{
    pid_t pid;
    
    printf("%d\n","abcd");
    printf("开始");

    pid=fork();
    switch(pid)
    {
        case 0:
            while(1)
            {
                printf( "我是子进程getpid%d,我的父进程getppid%d\n",getpid(),getppid());
                sleep(3);
            }
        case -1:printf("进程创建失败");break;
        default:
            printf("我是父进程getpid%d,我的子进程pid%d,我自己的父进程getppid%d,我死了\n",getpid(),pid,getppid());
            exit(0);

    }
}
