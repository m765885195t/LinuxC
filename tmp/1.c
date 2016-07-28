/*************************************************************************
	> File Name: 1.c
	> Author:motian 
	> Mail:765885195@qq.com 
	> Created Time: 2016年07月28日 星期四 09时10分36秒
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>


//奇怪的vfork()  共用的后果,栈替换


void stack1()
{
    vfork();
}

void stack2()
{
    _exit(0);
}

int main()
{
    
    stack1();

    printf("%d 1\n",getpid());
    stack2();

    printf("%d 2\n",getpid());
    return 0;
}

