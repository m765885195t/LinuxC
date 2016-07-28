/*************************************************************************
	> File Name: incrprint.c
	> Author:motian 
	> Mail:765885195@qq.com 
	> Created Time: 2016年07月28日 星期四 17时53分23秒
 ************************************************************************/

#include<stdio.h>
#include<pthread.h>
#include<unistd.h>

int counter=0;

int main()
{

    pthread_t t1;
    void *print_counter(void *);
    int i;

    pthread_create(&t1,NULL,print_counter,NULL);

    for(i=0;i<5;i++)
    {
        counter++;
        sleep(1);
    }

    pthread_join(t1,NULL);

}

void *print_counter(void *m)
{
    int i;
    for(i=0;i<5;i++)
    {
        printf("counter = %d\n",counter);
        sleep(1);
    }
    
    return NULL;
}
