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
    struct sockaddr_in their_addr;
    int i=0;

    //初始化服务器端地址
    their_addr.sin_family=AF_INET;
    their_addr.sin_port=htons(2323); //端口
   inet_aton("192.168.30.219",&their_addr.sin_addr);  //
   // their_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
    bzero(&(their_addr.sin_zero),8);

    
    //建立TCP套接口
    sock_fd = socket(AF_INET,SOCK_STREAM,0);

    //连接服务器

    connect(sock_fd,(struct sockaddr *)&their_addr,sizeof(struct sockaddr_in));
    
    //向服务器发送字符串
    char a[128];

    while(1)
    {
        printf("客户端:");
        fgets(a,128,stdin);
        a[strlen(a)-1]='\0';

        send(sock_fd,a,strlen(a),0);
    
        //接受从服务器返回的信息
        numbytes=recv(sock_fd,buf,100,0);
        buf[numbytes]='\0';
        printf("服务器:");
        printf("%s\n",buf);
    
    }

    close(sock_fd);

    return 0;
}
