/*************************************************************************
    > File Name: fcntl_lock.c
    > Author:motian 
    > Mail:765885195@qq.com 
    > Created Time: 2016年07月23日 星期六 09时06分04秒
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

int main()
{
    int fd;
    int ret;
    char a[32];
    struct flock lock;
    
    memset(&lock,0,sizeof(struct flock));
    lock.l_start=SEEK_SET;
    lock.l_len=0;
    lock.l_whence= 0;
    
    if( (fd=open("tian",O_CREAT|O_RDWR|O_TRUNC,S_IRWXU))==-1 )
    {
        printf("文件打开失败");
    }
    
    if(write(fd,"mo tian",7) ==-1) 
    {
        printf("写数据有误");
    }
    lseek(fd,0,SEEK_SET);
    //加读锁
    
    lock.l_type=F_WRLCK;
    fcntl(fd,F_SETLK,lock);

       if((ret=read(fd,a,7)) <0)
        printf("读数据失败");
        a[7]='\0';
        printf("%s",a);
    
    getchar();

    
   
    
    //加写锁
    lock.l_type=F_WRLCK;
    if(fcntl(fd,F_SETLK,lock))
        printf("写锁失败");
    getchar();
    getchar();
    lseek(fd,0,SEEK_SET);
    read(fd,a,7);
    a[7]='\0';
    printf("%s",a);

    lock.l_type=F_UNLCK;
    fcntl(fd,F_SETLK,lock);
 }
