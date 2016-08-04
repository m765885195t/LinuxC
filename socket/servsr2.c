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
    char Y_name_ID[32];//接受人的名字或ID
    char content[256];//消息主体
    int state;            //1在线　0离线  2隐身  3聊天　4传文件 

}buf;

struct user_info *  find(int user_fd) //查找用户信息
{
    for(i=0;i<30;i++)
    {
        if(USER[i].ID == user_fd)
        {
            return USER[i];
        }
    }
    return NULL;
}

int len_data = sizeof(struct data_info);
//清空信息组(全置为0)





int main()   //主函数
{
    int sock_fd,user_fd; //套接字描述符
    struct sockaddr_in serv_addr,cli_addr;//服务器与登陆用户地址
    int addr_len = sizeof(struct sockaddr_in);

    //建立套接字
    if((sock_fd = socket(AF_INIT,SOCK_STRAM)) < 0)  //建立
    {
        perror("socket");
    }
    
    //设置属性
    int optval = 1;
    if(setsockopt(sock_fd,SOL_SOCKET,_SO_REUSEADDR,(void *)&optval,sizeof(int)) < 0)
    {
        perror("setsockopt");
    }

    //初始化地址结构
    serv_addr.sin_family = AF_INIT;
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

    printf("等待中.....");

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
        send(user_fd,WELCOME,strlen(WELCOME),0);

        //处理会话
        pthread_t p_t;
        pthread_create(&p_t,NULL,conversation, ||user_fd||);
        
    }
}

void conversation(int user_fd) //登录主界面
{
    struct data_info buf;

    memset(&buf,0,len_info);
    strcpy(buf.content,"1:用户登录\n2:用户注册");
    buf.chat=0;

    send(user_fd,&buf,len_data,0);
    
    while(1)
    {
        memset(&buf,0,len_info);
        recv(user_fd,&buf,len_info,0);

        if(strcmp(buf.content,"1") == 0)
        {
            login();
            break;
        }
        if(strcmp(buf.content,"2") == 0)
        {
            zhuce();
            break;
        }
        memset(&buf,0,len_info);
        strcpy(buf.content,"你的选择有误,请重新输入");
        send(user_fd,&buf,len_info,0);
    }
}

void login(int user_fd)   //登录函数
{
    struct data_info buf;
    char userID[32];
    char password[32];
    char a[]="用户跟密码不匹配!!!";
    int len,flag = 1;

    memset(&buf,0,len_buf);
    strcpy(buf.content,"---登录---\n");
    send(user_fd,&buf,len_info,0);

    while(1)
    {
        memset(&buf,0,len_info);
        strcpy(buf.content,"username/ID:");
        send(user_fd,&buf,len_info,0);
        memset(&buf,0,len_info);                   //输入账号
        recv(user_fd,&buf,len_info,0);
        strcpy(buf.content,userID);

        memset(&buf,0,len_info);
        strcpy(buf.content,"password:");
        send(user_fd,&buf,len_info,0);
        memset(&buf,0,len_info);               //输入密码
        recv(user_fd,&buf,len_info,0);
        strcpy(buf.content,password);   
    
        for(i=0;i<30;i++)
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
            MAIN(USER[i].I_fd);
        }
        else
        {
            memset(&buf,0,len_info);
            strcpy(buf.content,"用户跟密码不匹配!!!");
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


    memset(&buf,0,len_buf);
    strcpy(buf.content,"---注册---\n");
    send(user_fd,&buf,len_info,0);
    
    while(1)
    {
        memset(&buf,0,len_info);
        strcpy(buf.content,"请输入你的用户名:");
        send(user_fd,&buf,len_info,0);
        memset(&buf,0,len_info);                   //输入账号
        recv(user_fd,&buf,len_info,0);
        strcpy(buf.content,username);

        memset(&buf,0,len_info);
        strcpy(buf.content,"请输入你的密码:");
        send(user_fd,&buf,len_info,0);
        memset(&buf,0,len_info);               //输入密码
        recv(user_fd,&buf,len_info,0);
        strcpy(buf.content,password);   
        
        memset(&buf,0,len_info);
        strcpy(buf.content,"请再次确认密码");
        send(user_fd,&buf,len_info,0);
        memset(&buf,0,len_info);               //确认密码
        recv(user_fd,&buf,len_info,0);
        strcpy(buf.content,password2);   
        
        if(strcmp(password,password2) == 0)
        {
            break;
        }
        else
        {
            mdemset(&buf,0,len_info);
            strcpy(buf.content,"两次密码不一致请重新输入\n");
            send(user_fd,&buf,len_info,0);
        }
    }

    for(i=0;i<30;i++)
    {
        if(USER[i].man == 0)
        {
            strcpy(USER[i].name,username);
            strcpy(USER[i].pass,password);
            USER[i].I_fd = user_fd;
            USER[i].man = 1;

            login(user_fd);
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

        for(i=0;i<30;i++)
        {
            if(strcmp(USER[i],buf.content) == 0)
            {
                if(USER[i].state == 1)
                {
                    memset(&buf,0,256);
                    strcpy(buf.content,"发送请求中...");
                    send(user_fd,&buf,len_info,0);


                    memset(&buf,0,256);
                    strcpy(buf.content,user->name);
                    strcat(buf.content,"请求连接");
                    send(USER[i].I_fd,);

                    memset(&buf,0,256);
                    send(user_fd,&buf,len_info,0);
                    recv(user_fd,&buf,len_info,0);
                    
                    if(strcpy())
                    
                }
                else
                {
                    memset(&buf,0,256);
                    strcpy(buf.content,"对方离线中....");
                    send(user_fd,&buf,len_info,0);
                    break;
                }

            }
        }


    while(1)
    {
        
    

    }
}
