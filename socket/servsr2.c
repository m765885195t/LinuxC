/*************************************************************************
	> File Name: servsr2.c
	> Author:motian 
	> Mail:765885195@qq.com 
	> Created Time: 2016年08月04日 星期四 11时41分05秒
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<pthread.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>


#define WELCOME "|------欢迎来到聊天室------|\n"

struct user_info{             //用户信息
    char ID[6];
    char name[32];
    char pass[32];
    int I_fd;
    int state;      //0离线1在线2隐身
    int man;         //1表示有人,0无人
}USER[30],*USERp;

struct data_info{       //消息结构体
    char I_name_ID[32];//发送人的名字或ID
    int I_fd;
    char Y_name_ID[32];//接受人的名字或ID
    int Y_fd;
    char content[256];//消息主体
    int state;            //1在线　0离线  2隐身  3聊天　4传文件 
    int lianjie;   //连接状态
    int denglu;    //登录状态


}buf;

struct huihua{
    int l_fd;
    int r_fd;
};

struct user_info *  find(int user_fd) //查找用户信息
{
    for(int i=1;i<30;i++)
    {
        if(USER[i].I_fd == user_fd)
        {
            return &USER[i];
        }
    }
    return NULL;
}

int len_info = sizeof(struct data_info);
int len_user = sizeof(struct user_info);



void *conversation(void *fd);
void login(int user_fd);
void zhuce(int user_fd);
void MAIN(int user_fd);
void chat(int user_fd);
void *noc(void *a);


int main()   //主函数
{
    memset(USER,0,30*(len_user));
    int sock_fd,user_fd; //套接字描述符
    struct sockaddr_in serv_addr,cli_addr;//服务器与登陆用户地址
    int len_addr = sizeof(struct sockaddr_in);

    //建立套接字
    if((sock_fd = socket(AF_INET,SOCK_STREAM,0)) < 0)  //建立
    {
        perror("socket");
    }
    
    //设置属性
    int optval = 1;
    if(setsockopt(sock_fd,SOL_SOCKET,SO_REUSEADDR,(void *)&optval,sizeof(int)) < 0)
    {
        perror("setsockopt");
    }

    //初始化地址结构
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(4567);
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    memset(serv_addr.sin_zero,0,len_addr);

    //绑定接口
    if(bind(sock_fd,(struct sockaddr *)&serv_addr,len_addr) < 0)
    {
        perror("bind");
    }

    //设置监听接口
    if(listen(sock_fd,50) < 0)
    {
        perror("listen");
    }

    printf("等待中.....\n");

    while(1)
    {
        int num = 1;  //登录用户个数(管理员)
        //建立连接
        if((user_fd = accept(sock_fd,(struct sockaddr *)&cli_addr,&len_addr)) < 0)
        {
            perror("accept");
        }

        printf("新的连接上线了 ip: %s\n",inet_ntoa(cli_addr.sin_addr));

        //发送问候
        memset(&buf,0,len_info);
        strcpy(buf.content,WELCOME);
        send(user_fd,&buf,len_info,0);

        //处理会话
        pthread_t p_t;
        pthread_create(&p_t,NULL,conversation,(void *)&user_fd);
        
    }
}

void *conversation(void *fd) //登录主界面
{
    struct data_info buf;
    int user_fd;
    user_fd = *((int *)fd);

    memset(&buf,0,len_info);
    strcpy(buf.content,"1:用户登录\n2:用户注册");

    send(user_fd,&buf,len_info,0);
    
    while(1)
    {
        memset(&buf,0,len_info);
        recv(user_fd,&buf,len_info,0);
        {

        }

        if(strcmp(buf.content,"1") == 0)
        {
            login(user_fd);
            break;
        }
        if(strcmp(buf.content,"2") == 0)
        {
            zhuce(user_fd);
            break;
        }
        memset(&buf,0,len_info);
        strcpy(buf.content,"你的选择有误,请重新输入!");
        send(user_fd,&buf,len_info,0);
    }
}

void login(int user_fd)   //登录函数
{
    struct data_info buf;
    char userID[32];
    char password[32];
    int len,flag = 0,i;

    memset(&buf,0,len_info);
    strcpy(buf.content,"---登录---\n");
    send(user_fd,&buf,len_info,0);

    while(1)
    {
        memset(&buf,0,len_info);
        strcpy(buf.content,"username/ID:");
        send(user_fd,&buf,len_info,0);
        memset(&buf,0,len_info);                   //输入账号
        recv(user_fd,&buf,len_info,0);
        strcpy(userID,buf.content);

        

        memset(&buf,0,len_info);
        strcpy(buf.content,"password:");
        send(user_fd,&buf,len_info,0);
        memset(&buf,0,len_info);               //输入密码
        recv(user_fd,&buf,len_info,0);
        strcpy(password,buf.content);   
    
    
        for(i=1;i<30;i++)
        {
            if(strcmp(userID,USER[i].name) == 0 || strcmp(userID,USER[i].ID))
            {
                if(strcmp(password,USER[i].pass) == 0)
                {
                    flag=1;//匹配成功
                    break;
                }
            }
        }
        if(flag)
        {
            USER[i].I_fd = user_fd;//为登录用户分配套接字
            USER[i].state = 1;
            memset(&buf,0,len_info);
            buf.denglu=1;
            send(USER[i].I_fd,&buf,len_info,0);//登陆成功的标识

            printf("%d  %d\n",USER[i].state,i);
            MAIN(USER[i].I_fd);
            break;
        }
        else
        {
            printf("%s\n","no");
            memset(&buf,0,len_info);
            strcpy(buf.content,"用户跟密码不匹配!!!\n");
            send(user_fd,&buf,len_info,0);
        }
    }
}

void zhuce(int user_fd)  //注册函数
{
    struct data_info buf;
    char username[32];
    char password[32];
    char password2[32];
    int i;

    memset(&buf,0,len_info);
    strcpy(buf.content,"---注册---");
    send(user_fd,&buf,len_info,0);
    
    while(1)
    {
        memset(&buf,0,len_info);
        strcpy(buf.content,"请输入你的用户名:");
        send(user_fd,&buf,len_info,0);
        memset(&buf,0,len_info);                   //输入账号
        recv(user_fd,&buf,len_info,0);
        strcpy(username,buf.content);
            
    


        memset(&buf,0,len_info);
        strcpy(buf.content,"请输入你的密码:");
        send(user_fd,&buf,len_info,0);
        memset(&buf,0,len_info);               //输入密码
        recv(user_fd,&buf,len_info,0);
        strcpy(password,buf.content);   
        

        memset(&buf,0,len_info);
        strcpy(buf.content,"请再次确认密码:");
        send(user_fd,&buf,len_info,0);
        memset(&buf,0,len_info);               //确认密码
        recv(user_fd,&buf,len_info,0);
        strcpy(password2,buf.content);   
        



        if(strcmp(password,password2) == 0)
        {
            break;
        }
        else
        {
            memset(&buf,0,len_info);
            strcpy(buf.content,"两次密码不一致请重新输入\n");
            send(user_fd,&buf,len_info,0);
        }
    }

    for(i=1;i<30;i++)
    {
        if(USER[i].man == 0)
        {
            strcpy(USER[i].name,username);
            strcpy(USER[i].pass,password);
            USER[i].I_fd = user_fd;
            USER[i].man = 1;

            login(USER[i].I_fd);
            break;
        }
    }
}

void MAIN(int user_fd)
{
    struct data_info buf;
    

    while(1)
    {
        memset(&buf,0,len_info);
        strcpy(buf.content,"1:聊天\n2:群聊\n");
        send(user_fd,&buf,len_info,0);
        
        memset(&buf,0,len_info);
        recv(user_fd,&buf,len_info,0);

        if(strcmp(buf.content,"1") == 0)
        {
            chat(user_fd);
        }
        if(strcmp(buf.content,"2") == 0)
        {
            
        }   
    }
}

void chat(int user_fd)
{
    struct data_info buf;
    struct user_info *user;
    struct huihua fd;
    int i;
    user = find(user_fd);

    memset(&buf,0,len_info);
    strcpy(buf.content,"---聊天开始---\n");
    send(user_fd,&buf,len_info,0);
    
    while(1)
    {
        memset(&buf,0,len_info);
        strcpy(buf.content,"你要和谁聊:");
        send(user_fd,&buf,len_info,0);


        memset(&buf,0,len_info);
        recv(user_fd,&buf,len_info,0);

        for(i=1;i<30;i++)
        {
            if(strcmp(USER[i].name,buf.content) == 0)
            {
                printf("%s\n","找到");
                printf("%d  %d\n",USER[i].state,i);
                if(USER[i].state == 1)
                {
                    memset(&buf,0,256);
                    strcpy(buf.content,"发送请求中...");
                    send(user_fd,&buf,len_info,0);


                    memset(&buf,0,len_info);
                    strcpy(buf.content,user->name);
                    strcat(buf.content,":请求连接");
                    strcpy(buf.Y_name_ID,user->name);
                    buf.Y_fd = user_fd;

                    send(USER[i].I_fd,&buf,len_info,0);

                    memset(&buf,0,len_info);
                    recv(USER[i].I_fd,&buf,len_info,0);

                    printf("%s\n",buf.content);
                    
                    if(strcmp(buf.content,"yes") == 0)
                    {
                        memset(&buf,0,len_info);
                        strcpy(buf.content,"聊天开始");
                        recv(user_fd,&buf,len_info,0);
                        recv(USER[i].I_fd,&buf,len_info,0);

                        fd.l_fd=user_fd;
                        fd.r_fd=USER[i].I_fd;
                        pthread_t t;
                        pthread_create(&t,NULL,noc,(void *)&fd);
                        break;
                    }       
                }
                else
                {
                    memset(&buf,0,len_info);
                    strcpy(buf.content,"对方离线中....");
                    send(user_fd,&buf,len_info,0);
                    break;
                }

            }
        }

    }
}

void *noc(void *a)
{
    struct huihua *fd=a;
    pid_t pid;
    pid = fork();
    while(1)
    {
        if(pid > 0)
        {
            memset(&buf,0,256);
            recv(fd->l_fd,&buf,len_info,0);
            if(strcmp(buf.content,"tuichu") == 0)
            {
                memset(&buf,0,256);
                strcpy(buf.content,"tuichu");
                send(fd->l_fd,&buf,len_info,0);
                return (0);
            }
            send(fd->r_fd,&buf,len_info,0);
        }   
        if(pid == 0)
        {
            memset(&buf,0,256);
            recv(fd->r_fd,&buf,len_info,0);
            if(strcmp(buf.content,"tuichu") == 0)
            {
                memset(&buf,0,256);
                strcpy(buf.content,"tuichu");
                send(fd->l_fd,&buf,len_info,0);
                exit(0);
            }
            send(fd->l_fd,&buf,len_info,0);
        }
    }
}


