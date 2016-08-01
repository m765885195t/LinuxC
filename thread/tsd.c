/*************************************************************************
	> File Name: tsd.c
	> Author:motian 
	> Mail:765885195@qq.com 
	> Created Time: 2016年08月01日 星期一 09时26分22秒
 ************************************************************************/

#include<stdio.h>
#include<pthread.h>
#include<string.h>
                     //警告的原因
pthread_key_t key;

void *thread2(void *arg)
{
    int tsd=5;
    printf("线程ID%ld\n",pthread_self());
    pthread_setspecific(key, (void *) tsd );
    printf("1线程ID%ld返回%d\n",pthread_self(),pthread_getspecific(key));
}

void *thread1(void *arg)
{
    int tsd=0;
    pthread_t thid2;

    printf("线程ID%ld\n",pthread_self());
    pthread_setspecific (key,(void*)tsd);
    pthread_create(&thid2,NULL,thread2,NULL);
    sleep(5);
    printf("2线程ID%ld返回%d\n",pthread_self(),pthread_getspecific(key));
}

int main(void)
{
    pthread_t thid1;
    printf("main开始\n");
    pthread_key_create(&key,NULL);
    pthread_create(&thid1,NULL,thread1,NULL);
    sleep(7);
    pthread_key_delete(key);
    printf("main结束\n");
    return 0;
}

