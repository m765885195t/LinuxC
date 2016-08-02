/*************************************************************************
	> File Name: condition2.c
	> Author:motian 
	> Mail:765885195@qq.com 
	> Created Time: 2016年08月01日 星期一 15时19分07秒
 ************************************************************************/

#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

pthread_mutex_t mutex;
pthread_cond_t cond;

void *thread1(void *);
void *thread2(void *);

int i=1;

int main(void)
{
    pthread_t t1,t2;
    pthread_mutex_init(&mutex,NULL);
    pthread_cond_init(&cond,NULL);
    
    pthread_create(&t1,NULL,thread1,NULL);
    pthread_create(&t2,NULL,thread2,NULL);
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);

    exit(0);
}


void *thread1(void *junk)
{
    for(i=1;i<7;i++)
    {
        pthread_mutex_lock(&mutex);
        printf("thread1:lock %d\n",__LINE__);
        if(!(i%3))
        {
            printf("thread1: lock %d\n",__LINE__);
            pthread_cond_signal(&cond);
            printf("thread1: signal2 %d\n",__LINE__);
            sleep(1);
        }
        pthread_mutex_unlock(&mutex);
        printf("thread1: unlock %d\n\n",__LINE__);
        sleep(1);
    }

}

void *thread2(void *junk)
{
    while(i<6)
    {
        pthread_mutex_lock(&mutex);
        printf("thread2: lock %d\n",__LINE__);
        if(i%3)
        {
            printf("thread2: wait 1 %d\n",__LINE__);
            pthread_cond_wait(&cond,&mutex);
            printf("thread2: wait 2 %d\n",__LINE__);
        }

        pthread_mutex_unlock(&mutex);
        printf("thread2 :unlock %d\n\n",__LINE__);
        sleep(1);
    }
}



