/*************************************************************************
	> File Name: condition3.c
	> Author:motian 
	> Mail:765885195@qq.com 
	> Created Time: 2016年08月01日 星期一 16时26分36秒
 ************************************************************************/

#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

void *thread1(void *);
void *thread2(void *);

pthread_cond_t cond;
pthread_mutex_t mutex;

int i;      

int main(void)
{
    pthread_t t1,t2;

    pthread_cond_init(&cond,NULL);   //初始化条件变量
    pthread_mutex_init(&mutex,NULL); //初始化互斥锁

    pthread_create(&t1,NULL,thread1,NULL); //创建线程
    pthread_create(&t2,NULL,thread2,NULL); 

    pthread_join(t1,NULL); //等待线程结束
    pthread_join(t2,NULL); 
    
    pthread_cond_destroy(&cond);    //清除条件变量和互斥锁
    pthread_mutex_destroy(&mutex);

    exit(0);
}

void *thread1(void *arg)
{
    for(i=1;i<6;i++)
    {
        pthread_mutex_lock(&mutex);    //给互斥锁加锁
       
        printf("xiyoulinux\n");
        
        if(i==3)
        {
            pthread_cond_signal(&cond);    //发射信号唤醒thread2
        }   
       
        pthread_mutex_unlock(&mutex);  //解锁 
        sleep(1);
    } 
}

void *thread2(void *arg)
{

    pthread_mutex_lock(&mutex);
    
    pthread_cond_wait(&cond,&mutex);  //先等待thread1解锁，然后等待被信号唤醒
 
    printf("motian\n");
   
    pthread_mutex_unlock(&mutex);
}
