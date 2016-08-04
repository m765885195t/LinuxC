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
    struct hotent *he;
    struct sockaddr_in their_addr;
    int i=0;

    //初始化服务器端地址
    their_addr.sin_family=AF_INET;
    their_addr.sin_port=htons(4567); //端口
   inet_aton("192.168.30.219",&their_addr.sin_addr);  //
   // their_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
    bzero(&(their_addr.sin_zero),8);

    
    //建立TCP套接口
    sock_fd = socket(AF_INET,SOCK_STREAM,0);

    //连接服务器

    connect(sock_fd,(struct sockaddr *)&their_addr,sizeof(struct sockaddr_in));
    
    char buf[256];
    pid_t pid;
    int flag=0;

    memset(buf,0,256);
    numbytes = recv(sock_fd,buf,100,0);
    buf[numbytes]='\0';
    printf("\n%s\n",buf);

    //向服务器发送字符串

    pid = fork();
    while(1)
    {
        if(pid > 0)
        {
            fgets(buf,256,stdin);//父进程发信息
            buf[strlen(buf)]='\0';
            send(sock_fd,buf,strlen(buf),0);
            memset(buf,0,256);
        }
        else if(pid == 0)
        {
            memset(buf,0,256);//收信息
            numbytes = recv(sock_fd,buf,256,0);
            buf[numbytes]='\0';
            if(strcmp("OK",buf) == 0)
            {
                send(sock_fd,"xiaxian",7,0);
                break;
            }
            printf("%s\n",buf);
        }
    }

    close(sock_fd);

    return 0;
}
