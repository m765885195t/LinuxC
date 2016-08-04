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
#include<pthread.h>

#define WELCOME "|--------欢迎进入聊天室--------|\n"


void *noc(void *a);
void gong(int fd);
void *deng(void *b);

char buf[256];
struct data{
    int new_fd;
    char username[128];
    char password[128];
};

struct huihua{
    int l_fd;
    int r_fd;
};

struct data xinxi[4]={{4,"111","111"},{5,"222","222"},{6,"333","333"},{7,"444","444"}};


void * deng(void *a)
{
    int fd=*( (int *)a);
    int flag=0,len;
    char username[256];
    char password[256];
    char buf[256];
    memset(username,0,256);
    memset(password,0,256);


    send(fd,"username:",9,0);
    memset(buf,0,256);

    len = recv(fd,buf,256,0);
    buf[len-1]='\0';
    
    strcpy(username,buf);      //用户名
    
    send(fd,"password:",9,0);
    memset(buf,0,256);

    len = recv(fd,buf,256,0);
    buf[len-1]='\0';

    strcpy(password,buf);      //密码
    
    for(int i=0;i<4;i++)
    {
        if(strcmp(xinxi[i].username,username) == 0)
        {
            if(strcmp(xinxi[i].password,password) == 0)
            {
                send(fd,"dengluchenggong\n",16,0);
                gong(fd);
            }
        }
    }

    return 0;
}



void gong(int fd)
{
    char buf[256]="1.单聊\n2.群聊";
    int len,flag=0,k;
    pthread_t p_t;

    while(1)
    {

        send(fd,buf,strlen(buf),0);

        memset(buf,0,256);
        len = recv(fd,buf,256,0);
        buf[len-1]='\0';
    
        if(strcmp(buf,"1") == 0)
        {
           //应该有在线用户表
            send(fd,"who",3,0);
            memset(buf,0,256);

            len=recv(fd,buf,256,0);
            buf[len-1]='\0';

            for(int i=0;i<4;i++)
            {
                if(strcmp(xinxi[i].username,buf) == 0)
                {
                    flag=1;
                    k=i;
                }
            }
            if(flag)
            {
                memset(buf,0,256);
                send(xinxi[k].new_fd,"qingquilainjie",14,0);

                memset(buf,0,256);
                len=recv(xinxi[k].new_fd,buf,256,0);
                buf[len-1]='\0';
                        
                if(strcmp(buf,"tongyi") == 0)
                {
                    memset(buf,0,256);
                    send(fd,"tongyi",6,0);


                    struct huihua h;
                    h.l_fd=fd;
                    h.r_fd=xinxi[k].new_fd;
       
                    pthread_create(&p_t,NULL,noc,(void *)&h);//开线程处理
                }
            }
            else
            {
                memset(buf,0,256);
                send(fd,"not",3,0);
            }
        }
        if(strcmp(buf,"2") == 0)
        {
            //群聊
        }
    }
}


void *noc(void *a)
{
    struct huihua *h=a;
    char buf[256];
    int len;
    pid_t pid;

    recv(h->l_fd,"kaishi",6,0);
    recv(h->r_fd,"kaishi",6,0);
    pid=fork();     
    while(1)
    {
        if(pid>0)
        {
            len=recv(h->l_fd,buf,256,0);
            buf[len]='\0';
            send(h->r_fd,buf,strlen(buf),0);
        }
        if(pid==0)
        {
            len=recv(h->r_fd,buf,256,0);
            buf[len]='\0';
            send(h->l_fd,buf,strlen(buf),0);
        }
    }
}

int main()
{
    int sock_fd,new_fd;  //套接字描述符
    int sin_size,numbytes;
    struct sockaddr_in serv_addr,cli_addr; //套接字地址
    int len_addr = sizeof(struct sockaddr_in);
    char buf[128];


    if((sock_fd = socket(AF_INET,SOCK_STREAM,0)) < 0)  //建立TCP套接字
    {
        perror("socket");
    }


    //设置套接字的属性使之可以重新绑定接口
    int optval=1;
    if(setsockopt(sock_fd,SOL_SOCKET,SO_REUSEADDR,(void *)&optval,sizeof(int)) < 0)
    {
        perror("setsockopt");
    }


    //初始化服务器端地址结构 
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_port = htons(4567); //端口号  
    serv_addr.sin_addr.s_addr=htonl(INADDR_ANY); //ip地址
    memset(serv_addr.sin_zero,0,len_addr);

    //绑定端口
    
    if(bind(sock_fd,(struct sockaddr *)&serv_addr,len_addr) < 0)
    {
        perror("bind");
    }

    //设置位监听接口
    if(listen(sock_fd,20) < 0) //最多请求10个
    {
        perror("listen");
    }


    printf("等待中......\n");

    //等待连接
    int i=0,n=1,k;

    while(1)
    {
        //如果建立连接，则产生一个全新的套接字
        if((new_fd=accept(sock_fd,(struct sockaddr *)&cli_addr,&len_addr)) < 0)
        {
            perror("accept");
        }
        
        printf("新的连接上线了 ip:%s\n",inet_ntoa(cli_addr.sin_addr));
        int flag=0;
        pid_t pid;
        int len;

        xinxi[i].new_fd=new_fd;
        printf("%d\n",xinxi[i].new_fd);
        //发送问候
        send(xinxi[i].new_fd,WELCOME,strlen(WELCOME),0);

        //登录
        pthread_t p1;
        
        pthread_create(&p1,NULL,deng,(void *)&xinxi[i].new_fd);
        i++;
    }

    return 0;
}

