/*************************************************************************
	> File Name: twordcount.c
	> Author:motian 
	> Mail:765885195@qq.com 
	> Created Time: 2016年07月30日 星期六 09时42分52秒
 ************************************************************************/

#include<stdio.h>
#include<pthread.h>
#include<ctype.h>

struct arg_set
{
    char *filename;
    int count;
};

int main(int argc,char *argv[])
{
    pthread_t         t1,t2;
    struct arg_set    args1,args2;
    void *count_words(void*);

    args1.filename=argv[1];
    args1.count=0;
    pthread_create( &t1,NULL,count_words,(void *)&args1 );

    args2.filename=argv[2];
    args2.count=0;
    pthread_create( &t2,NULL,count_words,(void *)&args2 );

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);

    printf("%d %s\n%d %s\n%d\n",args1.count,argv[1],args2.count,argv[2],args1.count+args2.count);
}


void *count_words(void *a)
{
    struct arg_set *args = a;
    FILE *fp;
    int c,prevc = '\0';

    fp=fopen(args->filename,"r");
    {
        while( (c=getc(fp))!=EOF )
        {
            if(!isalnum(c) && isalnum(prevc) )
            {
                args->count++;
            }
            prevc = c;
        }
        fclose(fp);
    }

    return NULL;
}
