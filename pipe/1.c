/*************************************************************************
	> File Name: 1.c
	> Author:motian 
	> Mail:765885195@qq.com 
	> Created Time: 2016年07月27日 星期三 17时28分41秒
 ************************************************************************/

#include<stdio.h>
#include<sys/stat.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>

#define FIFO_READ    "01"   //读管道
#define FIFO_WRITE   "10"  //写管道

int main(void)
{
    int wfd,rfd;   // 两个管道的读写文件符
    int len;
    char rbuf[1024],wbuf[1024];

    umask(0);
    mkfifo(FIFO_WRITE,S_IFIFO|0666);  //创建一个写管道,用它来写;

    umask(0);
    wfd = open(FIFO_WRITE,O_WRONLY); //打开写管道

    while((rfd=open(FIFO_READ,O_RDONLY)==-1))
    {
        printf("www\n");
        sleep(1);            
    }
    
   // wfd = open(FIFO_WRITE,O_WRONLY); //打开写管道
    while(1)
    {
        
//        len=read(rfd,rbuf,1024);
  //      if(len>0)
    //    {
      //      rbuf[len]='\0';
        //    printf("2:%s\n",rbuf);
       // }
        
        printf("1:");                   //自己
        fgets(wbuf,1024,stdin);          //写消息
        wbuf[strlen(wbuf)-1]='\0';

        if(strcmp(wbuf,"q")==0)             //q退出
        {
            close(wfd);                    //先关写端管道
            unlink(FIFO_WRITE);             //删除写管道
            close(rfd);                     //再关读端管道
            exit(0);
        }

        write(wfd,wbuf,strlen(wbuf));    // 写进写管道    
        len=read(rfd,rbuf,1024);           //从读管道读消息
                                           //好像读不出来
        printf("%s\n",rbuf);
        if(len>0)
        {
            rbuf[len]='\0';
            printf("2:%s\n",rbuf);  //打印对方的消息
        }

    }
}
