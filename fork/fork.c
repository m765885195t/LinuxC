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
    

    pid=vfork();
    
    if(pid<0){
        printf("fork error\n");
    }

    else if(pid==0){
        printf("子进程所属父进程的id%d\n",getppid());
        printf("子进程的pid%d\n",getpid());
        //getpgrp()相当于调用getpgid(0);
        printf("子进程所属的组id%d\n",getpgrp());
        printf("子进程所属的组id%d\n",getpgid(0));
        //getpgid()用来取得参数pid指定的进程所属的进程组码
        //参数为0则回去当前进程的组码;
        printf("子进程所属的组id%d\n",getpgid(getpid()));
        exit(0);
    }
    
    printf("父进程的id%d\n",getpid());
    printf("父进程是该进程组的组长\n");
    printf("父进程所属的组id%d\n",getpgid(0));
    return 0;
}
