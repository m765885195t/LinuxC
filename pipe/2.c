/*************************************************************************
	> File Name: 2.c
	> Author:motian 
	> Mail:765885195@qq.com 
	> Created Time: 2016年07月27日 星期三 21时42分53秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>

#define FIFO_READ   "10"
#define FIFO_WRITE  "01"

int main(void)
{
    int rfd,wfd;
    int len;
    char rbuf[1024],wbuf[1024];

    umask(0);
    mkfifo(FIFO_WRITE,S_IFIFO|0666);

    //umask(0);
    //wfd=open(FIFO_WRITE,O_WRONLY);

    while((rfd=open(FIFO_READ,O_RDONLY))==-1)
    {
        printf("lll\n");
        sleep(1);
    }

    wfd=open(FIFO_WRITE,O_WRONLY);

    /*
    while((rfd=open(FIFO_READ,O_RDONLY)==-1))
    {
        sleep(1);
    }
    */ //为什么交换了
    while(1)
    {
        
        len=read(rfd,rbuf,1024);
        if(len>0)
        {
            rbuf[len]='\0';
            printf("1:%s\n",rbuf);
        }

        printf("2:");

        fgets(wbuf,1024,stdin);
        wbuf[strlen(wbuf)-1]='\0';
        printf("|||%s|||\n",wbuf);
        if(strcmp(wbuf,"q")==0)
        {
            close(wfd);
            unlink(FIFO_WRITE);
            close(rfd);
            exit(0);

        }

        write(wfd,wbuf,strlen(wbuf));
       /*
        len=read(rfd,buf,1024);

        if(len>0)
        {
            buf[len]='\0';
            printf("1:%s\n",buf);
        
        }
        */


    }
}
