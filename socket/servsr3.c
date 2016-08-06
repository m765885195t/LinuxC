/*************************************************************************
	> File Name: servsr3.c
	> Author: 
	> Mail: 
	> Created Time: 2016年08月05日 星期五 18时42分21秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<pthread.h>
#include<arpa/inet.h>
#include<netinet/in.h>

struct user_info{          //用户信息结构体
//    long ID;//MT号
    char username[32];//用户名
    char password[16];//密码
    int fd;//用户套接字
    int man;//该位置有无用户
    int state;//0离线1在线2隐身   状态
    int pro;//0注册,1登录 

//    char autograph[256];
}USER[50],*USERp;

struct data_info{         //消息结构体
    char I_name[32];//自己的名字
//    long I_ID;      //ID;
    char Y_name[32];//对方的名字
//    long Y_ID;      //对方的ID
    char message[256];//消息住体
    int pro;
}rec,sen;

int len_data = sizeof(struct data_info);




//通过用户名查找用户
struct user_info * find(char *username)
{
    for(int i=1;i<50;i++)
    {
        if(strcmp(USER[i].username,username) == 0)
        {
            return &USER[i];
        }
    }

    return NULL;
}

int main()
{
    int sock_fd,user_fd;
    struct sockaddr_in ser_addr,cli_addr;
    int len_addr = sizeof(struct sockaddr_in);
    int optval = 1;

    if((sock_fd = socket(AF_INET,SOCK_STREAM,0)) < 0)
    {
        perror("socket");
    }
    
    if(setsockopt(sock_fd,SOL_SOCKET,SO_REUSEADDR,(void *)&optval,sizeof(int)) < 0)
    {
        perror("setsockopt");
    }

    memset(&ser_addr,0,len_addr);
    ser_addr.sin_family = AF_INET;
    ser_addr.sin_port = htons(4567);
    ser_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    
    if(bind(sock_fd,(struct sockaddr *)&ser_addr,len_addr) < 0)
    {
        perror("bind");
    }

    if(listen(sock_fd,50) < 0)
    {
        perror("listen");
    }

    printf("等待中....\n");

    while(1)
    {
        if((user_fd = accept(sock_fd,(struct sockaddr *)&cli_addr,&len_addr)) < 0)
        {
            perror("accept");
        }

        printf("新的连接上线了 ip: %s\n",inet_ntoa(cli_addr.sin_addr));

    //消息处理函数
    }

}

