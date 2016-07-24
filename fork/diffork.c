/*************************************************************************
	> File Name: diffork.c
	> Author:motian 
	> Mail:765885195@qq.com 
	> Created Time: 2016年07月23日 星期六 16时16分01秒
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>

int main(void)
{
    pid_t pid;
    int i=20,n=30,k=0;

//    pid=fork();
  pid=vfork();

    switch(pid)
    {
        case 0:
            printf("%d\n",getpid());
            while(i--)
            {
                printf("111\n");
                   k++;
                sleep(1);
            }
        printf("%d %d\n",getpid(),k);
        case -1:exit(0);
        default:
            printf("%d\n",getpid());
            while(n--)
            { 
                printf("222\n");
                k++;
                sleep(1);
            }
        printf("%d %d\n",getpid(),k);

    }
}
