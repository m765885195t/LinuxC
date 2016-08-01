/*************************************************************************
	> File Name: share.c
	> Author:motian 
	> Mail:765885195@qq.com 
	> Created Time: 2016年08月01日 星期一 10时25分49秒
 ************************************************************************/

#include<stdio.h>
#include<pthread.h>

static int a=1;
void *thread()
{                      //加入sleep为什么会警告 
    a=2;
    printf("新线程ID%ld\n",pthread_self());
    printf("a=%d\n",a);
}

int main()
{
    pthread_t t1;

    a=5;

    printf("主线程%d\n",a);
    pthread_create(&t1,NULL,thread,NULL);

    pthread_join(t1,NULL);
    sleep(1);    
    printf("主线程%d\n",a);

    pthread_join(t1,NULL);
    return 0;
}
