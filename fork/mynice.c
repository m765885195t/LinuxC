/*************************************************************************
	> File Name: mynice.c
	> Author:motian 
	> Mail:765885195@qq.com 
	> Created Time: 2016年07月25日 星期一 16时30分25秒
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/resource.h>
#include<sys/types.h>
#include<stdlib.h>

//实现的很简单

int main(void){
    
    pid_t pid;
    int stat_val=0;
    int oldpri,newpri;

    printf("改变进程优先级\n");

    pid=fork();

    if(pid<0){
        printf("进程创建失败");
        exit(1);
    }

    if(pid==0){
        printf("子进程\n");
        oldpri=getpriority(PRIO_PROCESS,0);
        printf("%d\n",oldpri);
        newpri=nice(2);
        printf("%d\n",newpri);
        exit(0);
    }

}
