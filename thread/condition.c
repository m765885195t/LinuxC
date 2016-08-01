/*************************************************************************
	> File Name: condition.c
	> Author:motian 
	> Mail:765885195@qq.com 
	> Created Time: 2016年08月01日 星期一 14时26分10秒
 ************************************************************************/

#include<stdio.h>
#include<pthread.h>
#include<unistd.h>

pthread_mutex_t mutex;
pthread_cond_t    cond;
                          //哪里出错了
void * thread1(void *arg)
{
    pthread_clean_push(pthread_mutex_unlock,&mutex);

    while(1)
    {
        printf("thread1开始\n");
        pthread_mutex_lock(&mutex);
        pthread_cond_wait(&cond,&mutex);
        printf("thread1应用condition\n");
        pthread_mutex_unlock(&mutex);
        sleep(4);
    }    

    pthread_cleanup_pop (0);
}
    void *thread2(void *arg)
{
    while(1)
    {
        printf("thread2开始\n");
        pthread_mutex_lock(&mutex);
        pthread_cond_wait(&cond,&mutex);
        printf("thread2应用condition\n");
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
}

int main()
{
    pthread_t tid1,tid2;

    printf("conition变化结论\n");
    pthread_mutex_init (&mutex,NULL);
    pthread_cond_init(&cond,NULL);
    pthread_create(&tid1,NULL,thread1,NULL);
    pthread_create(&tid2,NULL,thread2,NULL);

    do{
        pthread_cond_signal(&cond);
    }while(1);

    sleep(50);
    pthread_exit(0);

}

