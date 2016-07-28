/*************************************************************************
	> File Name: fork.c
	> Author:motian 
	> Mail:765885195@qq.com 
	> Created Time: 2016年07月26日 星期二 21时45分10秒
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
int main()
{
    int i;
    for(i=0;i<4;i++)
    {
        fork();
        printf("-");
    }
}
