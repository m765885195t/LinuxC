/*************************************************************************
	> File Name: oncerun.c
	> Author:motian 
	> Mail:765885195@qq.com 
	> Created Time: 2016年07月30日 星期六 10时37分32秒
 ************************************************************************/

#include<stdio.h>
#include<pthread.h>

pthread_once_t once = PTHREAD_ONCE_INIT;
                                             
void run(void)
{
    printf("%s 线程ID%ld\n",__FUNCTION__,pthread_self());
}

void * thread1(void *arg)
{
    printf("%s 线程ID%ld\n",__FUNCTION__,pthread_self());
    pthread_once(&once,run);
    printf("%s 结束\n",__FUNCTION__);
}

void * thread2(void *arg)
{
    printf("%s 线程ID%ld\n",__FUNCTION__,pthread_self());
    pthread_once(&once,run);
    printf("%s 结束\n",__FUNCTION__);
}

int main()
{
    pthread_t t1,t2;
    pthread_create(&t2,NULL,thread2,NULL);
    pthread_create(&t1,NULL,thread1,NULL);

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);

    printf("完成\n");
}
