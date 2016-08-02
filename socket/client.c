/*************************************************************************
	> File Name: client.c
	> Author:motian 
	> Mail:765885195@qq.com 
	> Created Time: 2016年08月02日 星期二 19时16分34秒
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/socket.h>

int main(int argc,char *argv[])
{
    int sock_fd,numbytes;
    char buf[100];
    struct hotent *he;
    struct sokaddr_int their_addr;
    int i=0;

    //将名字与地址转换
    he = gethostbyname(argv[1]);

    //建立TCP套接口
    sock_fd = socket(AF_INET,SOCK_STREAM,0);

    //初始化连接
    their_addr.sin_family=AF_INET;
    their_addr.sin_port=htons(2323);
    their_addr.sin_addr=*((struct in_addr*)he->h_addr);
    bzero(&(their_addr.sin_zero),8);

    //连接服务器

    connect(sock_fd,(struct sockaddr *)&their_addr,sizeof(struct sockaddr));

    //向服务器发送字符串
    send(sock_fd,"hello!",6,0);

    //接受从服务器返回的信息
    numbytes=recv(sock_fd,buf,100,0);
    buf[numbytes]='\0';
    printf("打印%s",buf);

    close(sock_fd);

    return 0;
}
