/*************************************************************************
	> File Name: servsr.c
	> Author:motian 
	> Mail:765885195@qq.com 
	> Created Time: 2016年08月02日 星期二 17时33分11秒
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<error.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

int main()
{
    int sock_fd,new_fd;  //套接字描述符
    int sin_size;
    struct sockaddr_in my_addr,their_addr; //套接字地址
    char buff[128];

    sock_fd = socket(AF_INET,SOCK_STREAM,0);  //建立TCP接口

    //初始化套接字
    my_addr.sin_family=AF_INET;
    my_addr.sin_port = htons(2323);
    my_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    bzero(&(my_addr.sin_zero),8);//将数组前８字节消零

    //绑定端口
    
    bind(sock_fd,(struct sockaddr *)&my_addr,sizeof(struct sockaddr));
    
    //设置位监听接口
    listen(sock_fd,10); //最多请求10个


    //等待连接
    while(1)
    {
        sin_size=sizeof(struct sockaddr_in);

        //如果建立连接，则产生一个全新的套接字
        new_fd=accept(sock_fd,(struct sockaddr *)&their_addr,&sin_size);

        //子进程完成回话，父进程监听
        if(!fork())
        {
            //读取客户端发来的信息

            recv(new_fd,buff,strlen(buff),0);

            printf("%s\n",buff);//打印

            //将发来的消息发回去
            send(new_fd,buff,strlen(buff),0);

            close(new_fd);
            exit(0);
        }

        close(new_fd);


    }

    close(sock_fd);
}

