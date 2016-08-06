/*************************************************************************
	> File Name: client3.c
	> Author: 
	> Mail: 
	> Created Time: 2016年08月06日 星期六 08时36分55秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/socket.h>

struct user_info{
    long ID;
    char username[32];
}USER;


struct data_info{
    char I_name[32];
//    long I_ID;
    char Y_name[32];
//    long Y_ID;
    char message[256];
    int pro; //1注册2登录3会话
}rec,sen;

int fd;

int len_data = sizeof(struct data_info);

int main()
{
    struct sockaddr_in ser_addr;
    int len_addr = sizeof(struct sockaddr_in);

    memset(&ser_addr,0,len_addr);
    ser_addr.sin_family = AF_INET;
    ser_addr.sin_port = HTONS(4567);
    inet_aton("192.168.30.219",&ser_addr.sin_addr);

    if((fd = socket(AF_INET,SOCK_STREAM,0)) < 0)
    {
        perror("socket");
    }

    if(connect(fd,(struct sockaddr *)&ser_addr,sizeof(struct sockaddr_in)) < 0)
    {
        perror("connect");
    }

    MAIN();
}

void MAIN(void)
{
    char buf[256];

    while(1)
    {
        system("clear");
        printf("---------------\n");
        printf("------莫天-----\n");
        printf("---------------\n");
        printf("1----登录------\n");
        printf("2----注册------\n");
    //    printf("3--忘记密码----\n");
        printf("4----退出------\n");
        printf("---------------\n");
        printf("请输入你的选择:\n");
        
        ch = getchar();
        switch(ch)
        {
            case '1':denglu();break;
            case '2':zhuce();break;
            case '3':
            case '4':exit(0);
            default:printf("你的输入有误,请重新输入\n");
        }
    }
}

void denglu(void)
{
    while(1)
    {
        system("clear");
        printf("请输入您的账号:\n"); //或ID
        gets(sen.I_name);
        strcpy(USER.username,sen.I_name);
        //USER.ID = 
        printf("请输入你的密码:\n");
        gets(sen.Y_name);
        
        sen.pro = 2;
        send(fd,&sen,len_data,0);
        recv(fd,&rec,len_data,0);
        if(strcmp(rec.message,"1") == 0)
        {
            lt();
        }
        else
        {
            printf("账号与密码不符合,请重新输入\n");//加上返回
        }
    }
}

void zhuce(void)
{
    char username[32];
    char password[32];
    char password[32];
    int id:

    while(1)
    {
        system("clear");
    //    printf("您的MT号为:%ld\n",id = get_ID());
    //    printf("此号具有全球唯一性,请放心使用\n");
        
        printf("请输您的用户名:\n");
        gets(username);
        printf("请输入你的密码(长度不能超过16位):\n");
        gets(passwor);
        printf("请在输入一次进行确认\n");
        gets(password2);

        if(strcmp(password,password2) == 0)
        {     
            strcpy(rec.I_name,username);
            strcpy(rec.Y_name,password);
            rec.pro = 1;
           // rec.I_ID = id;

            recv(fd,&rec,len_data,0);

            qiehaun();
        }
        else
        {
            printf("两次密码不一致,请重新注册.\n");//应该加上返回
        }
    }
}

long get_ID(void)
{
    static int i=100000;//应该随机

    return i++;
}

void qiehuan(void)
{
    while(1)
    {
        system("clear");
        printf("1-----返回上一层-------\n");
        printf("2------退出系统--------\n");
        printf("请输入你的选择:\n");

        ch = getchar();

        if(ch == '1')
        {
            break;
        }
        else if(ch == '2')
        {
            exit(0);
        }
        else 
        {
            printf("你的输入有误,请重新输入.\n");
        }
    }
}

void lt(void)
{
    while(1)
    {
        system("clear");
        printf("-------------");
        printf("1---私聊-----");
        printf("2---私群聊----");
        printf("3----群聊-----");
        printf("------------");

        ch = getchar();
        switch(ch)
        {
            case '1':sl();break;
            case '2':sql();break;
            case '3':ql();break;
            default:printf("你的输入有误,请重新输入.");
        }
    }
}

void zx(void) //在线
{

}

void sl(void)
{
    printf("---好友在线列表---\n");
    zx();
    printf("请输入你要聊天的用户name\n");
    gets(sen.Y_name);
    sen.I_name

}

void sql(void)
{

}

void ql(void)
{

}
