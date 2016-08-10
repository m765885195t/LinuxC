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
    char username[32];
    char password[16];
    int fd;
    int man;
    int state;//0离线1在线2隐身3正在聊天   状态

                 //    char autograph[:w256];
}USER[50],*USERp;


struct data_info{       //私聊消息结构体
    char I_name[32];
//    long I_ID;    
    char Y_name[32];
//    long Y_ID;      
    char message[256];
    int pro;//1注册2登录3请求4聊天5群聊6修改状态7好友在线表
};

struct ql_info{              //群聊信息结构体
    int fd;
    char message[256];
    char I_name[32];
//    long ID;
    int man;
}cy[50];



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
//通过成员名查找群成员
struct ql_info * find2(char *name)
{
    for(int i=1;i<50;i++)
    {
        if(strcmp(cy[i].I_name,name) == 0)
        {
            return &cy[i];
        }
    }
    return NULL;
}





void * session(void *a);





int main()
{
    int sock_fd,user_fd;
    struct sockaddr_in ser_addr,cli_addr;
    int len_addr = sizeof(struct sockaddr_in);
    int optval = 1;


    sock_fd = socket(AF_INET,SOCK_STREAM,0);
    setsockopt(sock_fd,SOL_SOCKET,SO_REUSEADDR,(void *)&optval,sizeof(int));

    memset(&ser_addr,0,len_addr);
    ser_addr.sin_family = AF_INET;
    ser_addr.sin_port = htons(4567);
    ser_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    
    bind(sock_fd,(struct sockaddr *)&ser_addr,len_addr);
    listen(sock_fd,50);

    printf("等待连接中....\n");

    while(1)
    {
        user_fd = accept(sock_fd,(struct sockaddr *)&cli_addr,&len_addr);

        printf("新的连接上线了 ip: %s\n",inet_ntoa(cli_addr.sin_addr));

    //消息处理函数
        
        pthread_t p_t;
        pthread_create(&p_t,NULL,session,(void *)&user_fd);
    }
}

void * session(void *a)
{
    int fd = *(int *)a;
    struct data_info sen,rec;
    int i;

    while(1)
    {
        recv(fd,&rec,len_data,0);

        if(rec.pro == 1)
        {
            puts("注册");

            printf("账号:%s,密码:%s\n",rec.I_name,rec.Y_name);
            for(i=1;i<50;i++)
            {
                if(USER[i].man == 0)
                {
                    USER[i].man = 1;
                    strcpy(USER[i].username,rec.I_name);
                    strcpy(USER[i].password,rec.Y_name);
                    break;
                }
            }
        }
        if(rec.pro == 2)
        {
            puts("登录");
            int flag = 0;
            for(i=1;i<50;i++)
            {
                if(USER[i].man == 1)
                {
                    if(strcmp(rec.I_name,USER[i].username) == 0)
                    {
                        if(strcmp(rec.Y_name,USER[i].password) == 0)
                        {
                            flag = 1;
                            break;
                        }
                    }
                }
            }
        
            if(flag)
            {
                USER[i].state = 1;
                USER[i].fd = fd;
                memset(sen.message,256,0);
                strcpy(sen.message,"1");
                send(fd,&sen,len_data,0);
                printf("%s上线了\n",USER[i].username);
            }
        }
        if(rec.pro == 3)
        {
            puts("请求");
            
            if((USERp = find(rec.Y_name)) != NULL)
            {
                if(USERp->state == 1)
                {
                    strcpy(sen.message,"OK");
                    send(fd,&sen,len_data,0);
                }
                else
                {  
                    strcpy(sen.message,"对方不在线或正在聊天中.\n");
                    send(fd,&sen,len_data,0);
                }
            }
            else
            {
                strcpy(sen.message,"查无此人");
                send(fd,&sen,len_data,0);
            }

        }
        if(rec.pro == 4)
        { 
            puts("私聊中");
            USERp = find(rec.Y_name);
            
            strcpy(sen.message,rec.message);
            strcpy(sen.Y_name,rec.Y_name);//转发消息
            strcpy(sen.I_name,rec.I_name);
            send(USERp->fd,&sen,len_data,0);
        }
        if(rec.pro == 5)
        {
            char s[2];
            int flag = 0;
            puts("群聊中");
            for(i=1;i<50;i++)
            {
                if(cy[i].man == 1)
                {
                    if(strcmp(cy[i].I_name,rec.I_name) == 0)
                    {
                        flag = 0;
                        break;
                    } 
                }
                else
                {
                    memset(cy[i].I_name,0,32);
                    strcpy(cy[i].I_name,rec.I_name);
                    cy[i].fd = fd;
                    cy[i].man = 1;
                    flag = 1; 
                    break;
                }
            }
            if(flag)
            {
                sprintf(s,"%d",i+1);
                s[strlen(s)]='\0';
                strcpy(sen.I_name,rec.I_name);
                strcpy(sen.message,"加入了,群聊人数共");
                strcat(sen.message,s);
                strcat(sen.message,"人\n");
            }
            else
            {
                if(strcmp(rec.message,"MT\n") == 0)
                {
                    sprintf(sen.message,"%s",rec.I_name,"退出了群组,","群聊人数共",i,"人");
                    cy
                }
                else
                {
                    strcpy(sen.message,rec.message);
                    strcpy(sen.I_name,rec.I_name);
                }
            }
            for(i=0;i<50;i++)
            {
                if(cy[i].man == 1)
                {
                    if(flag)
                    {
                        send(cy[i].fd,&sen,len_data,0);
                    }
                    else
                    {
                        if(strcmp(rec.I_name,cy[i].I_name) != 0)
                        {
                            send(cy[i].fd,&sen,len_data,0);
                        }
                    }
                }
            }
        }
        if(rec.pro == 6)
        {
            puts("状态");
            USERp = find(rec.I_name);
            int t;
            
            if(strcmp(rec.message,"MT") == 0)
            {
                USERp->state = 0;
                printf("%s下线了\n",USERp->username);
                return NULL;
            }
            if((strcmp(rec.message,"1") == 0) || (strcmp(rec.message,"2") == 0))
            {
                t = atoi(rec.message);
                USERp->state = t;
            }
            if(strcmp(rec.message,"ZT") == 0)
            {
                if(USERp->state == 2)
                {
                    memset(sen.message,0,256);
                    strcpy(sen.message,"隐身中...");
                }
                if(USERp->state == 1)
                {
                    memset(sen.message,0,256);
                    strcpy(sen.message,"在线中...");
                }
                send(fd,&sen,len_data,0);
            }
            if(strcmp(rec.message,"ZX") == 0)
            {
                USERp->state = 0;
            }
        }
        if(rec.pro == 7)
        {
            char s[3];
            for(i=1;i<50;i++)
            {
                if(USER[i].state == 1)
                {
                    sprintf(s,"%d",i);
                    s[strlen(s)]='\0';
                    memset(sen.message,0,256);
                    sprintf(sen.message,"%s%s%s",s," >     ",USER[i].username);
                    send(fd,&sen,len_data,0);
                }
            }
        }
    }
}


