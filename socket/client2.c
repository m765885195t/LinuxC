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
#include<pthread.h>

struct data_info{
    char I_name_ID[32];
    int I_fd;
    char Y_name_ID[32];
    int Y_fd;
    char content[256];
    int state;
    int lianjie;
    int denglu;
}buf;

int i;

void *fa(void *a);
void *shu(void *b);
int len_info = sizeof(struct data_info);


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
    i=sock_fd;

    connect(sock_fd,(struct sockaddr *)&their_addr,sizeof(struct sockaddr_in));

    pid_t pid;
    int flag=0;

    memset(&buf,0,len_info);
    recv(sock_fd,&buf,len_info,0);
    buf.content[strlen(buf.content)]='\0';
    printf("%s\n",buf.content);


    pthread_t t1,t2;
    pthread_create(&t1,NULL,fa,NULL);
    pthread_create(&t2,NULL,shu,NULL);
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
}


void *shu(void *a)
{
    while(1)
    {
        memset(&buf,0,len_info);
        fgets(buf.content,256,stdin);//父进程发信息
        buf.content[strlen(buf.content)-1]='\0';
        send(i,&buf,len_info,0);
    }
}

void *fa(void *b)
{
    while(1)
    {
        recv(i,&buf,len_info,0);
        if(buf.content[0]!="\0")
            printf("%s\n",buf.content);
    }
}

/*

    //向服务器发送字符串
    pid = fork();
    while(1)
    {
        if(pid > 0)
        {
            fgets(buf.content,256,stdin);//父进程发信息
            buf.content[strlen(buf.content)-1]='\0';
            if(strcmp(buf.content,"yes") == 0)
            {
         //    buf.Y_fd = 
            }
            send(sock_fd,&buf,len_info,0);
        }
        else if(pid == 0)
        {
            recv(sock_fd,&buf,len_info,0);

            
            
            printf("%s\n",buf.content);
        }
    }

    close(sock_fd);

    return 0;
}
*/
