/*************************************************************************
	> File Name: 10.c
	> Author: 
	> Mail: 
	> Created Time: 2016年08月11日 星期四 10时43分16秒
 ************************************************************************/

#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

void * a(void *f)
{
    printf("2:sasa\n");
    exit(0);
}
int main()
{
    pthread_t p_t;
    pthread_create(&p_t,NULL,a,NULL);
    sleep(1);
    printf("1qwqw\n");
    
}

