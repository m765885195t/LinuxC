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
    int pro; //1注册2登录3请求私聊4聊天5群聊
}rec,sen;

int fd;
int flag;

int len_data = sizeof(struct data_info);


void MAIN(void);
void denglu(void);
void zhuce(void);
void qiehuan(void);
void sl(void);
void ql(void);
void sql(void);
void* sll(void *a);
void lt(char name[]);
long get_ID(void);
void *session(void *a);
void MT(void);
void zx(void);
void hy(char name[]);
int qls(void);
void qz(void);
void smq(void);
void zt(void);



int main()
{
    struct sockaddr_in ser_addr;
    int len_addr = sizeof(struct sockaddr_in);

    memset(&ser_addr,0,len_addr);
    ser_addr.sin_family = AF_INET;
    ser_addr.sin_port = htons(4567);
    inet_aton("192.168.30.192",&ser_addr.sin_addr);

    fd = socket(AF_INET,SOCK_STREAM,0);

    if(connect(fd,(struct sockaddr *)&ser_addr,sizeof(struct sockaddr_in)) < 0)
    {
        printf("连接服务器失败,请检查服务器或网络\n");
        exit(0);
    }

    pthread_t p_t;
    pthread_create(&p_t,NULL,session,NULL);

    MAIN();
    pthread_join(p_t,NULL);
}










void *session(void *a)
{
    char b[100][1000];
    int i;
    while(1)//未读消息功能
    {
        recv(fd,&rec,len_data,0);

        if((sen.pro == 4) || (sen.pro == 5))//聊天退不出去
        {
            if(strcmp(rec.message,"MT") != 0)
            {   
                printf("%s >>> %s",rec.I_name,rec.message);
            } 
            else
            {
                flag = 1;
            }
        }

    }
}













void MAIN(void)
{
    char buf[256];

    while(1)
    {
        system("clear");
        printf("---------------\n");
        printf("------MT-----\n");
        printf("---------------\n");
        printf("1----登录------\n");
        printf("2----注册------\n");
        printf("3--忘记密码----\n");
        printf("4----使用说明-----\n");
        printf("5----退出------\n");
        printf("---------------\n");
        printf("请输入你的选择:\n");
        
        memset(buf,0,256);
        fgets(buf,256,stdin);
        if(strlen(buf) > 2)
        {
            continue;
        }

        if(buf[0] == '1')
        {
            denglu();
        }
        else if(buf[0] =='2')
        {
            zhuce();
        }
        else if(buf[0] == '3')
        {
            system("clear");
            printf("详请咨询<765885195>\n");
            getchar();
        }
        else if(buf[0] == '4')
        {
            //打开MT
        }
        else if(buf[0] == '5')
        {
            exit(0);            
        }
    }
}

void denglu(void)
{
    for(int i=0;i<3;i++)
    {
        sen.pro = 0;//清空消息标志
        system("clear");
        printf("---------MT登录----------\n\n");
        

        printf("请输入您的账号:"); //或ID
        memset(sen.I_name,32,0);
        fgets(sen.I_name,32,stdin);
        sen.I_name[strlen(sen.I_name)-1] = '\0';
        if(strlen(sen.I_name) > 16)
        {
            continue;
        }
        strcpy(USER.username,sen.I_name);//保存在信息里
        //USER.ID = 
        printf("请输入您的密码:");
        
        system("stty -echo");
        memset(sen.Y_name,32,0);
        fgets(sen.Y_name,32,stdin);
        sen.Y_name[strlen(sen.Y_name)-1] = '\0';
        system("stty echo");
        if(strlen(sen.Y_name) > 16)
        {
           continue;
        }

        sen.pro = 2;
        send(fd,&sen,len_data,0);
        
    
        printf("\n登录中......\n");
        sleep(1);
        
        if(strcmp(rec.message,"1") == 0)
        {    
            MT();
            i=-1;
        }
    }
}

void zhuce(void)
{
    char username[32];
    char password[32];
    char password2[32];
    int id;

    while(1)
    {
        sen.pro = 1;
        system("clear");
        printf("--------------注册--------\n\n");
    //    printf("您的MT号为:%ld\n",id = get_ID());
    //    printf("此号具有全球唯一性,请放心使用\n");



        printf("用户名:");
        memset(username,32,0);
        fgets(username,32,stdin);
        username[strlen(username)-1] = '\0';
        if(strlen(username) > 16)
        {
            continue;
        }


        printf("密码:");
        system("stty -echo");
        memset(password,32,0);
        fgets(password,32,stdin);
        password[strlen(password)-1] = '\0';
        system("stty echo");
        if(strlen(password) > 16)
        {
            continue;
        }
        
        printf("\n");
        printf("确认密码:");
        system("stty -echo");
        memset(password2,32,0);
        fgets(password2,32,stdin);
        password2[strlen(password2)-1] = '\0';
        system("stty echo");
        if(strlen(password2) > 16)
        {
            continue;
        }


        if(strcmp(password,password2) == 0)
        {     
            strcpy(sen.I_name,username);
            strcpy(sen.Y_name,password);
            sen.pro = 1;
           // rec.I_ID = id;
        
            send(fd,&sen,len_data,0);
            break;
        }
    }
}

long get_ID(void)
{
    static int i=100000;//应该随机

    return i++;
}

void MT(void)
{
    char buf[256];
    while(1)
    {
        sen.pro = 2;
        system("clear");
        printf("---欢迎进入MT室----\n\n");
        printf("-------------------\n");
        printf("1-------私聊-------\n");
        printf("2-------群聊-------\n");
        printf("3--------FTP-------\n");
        printf("4------修改状态----\n");
        printf("5-------注销-------\n");
        printf("6-------退出-------\n");
        printf("-------------------\n\n");

        printf("请输入你的选择:");
        memset(buf,0,256);
        fgets(buf,256,stdin);
        if(strlen(buf) > 2)
        {
            continue;
        }
        if(buf[0] == '1')
        {
            sl();
        }
        else if(buf[0] == '2')
        {
            ql();
        }
        else if(buf[0] == '3')
        {
//            ftp();//上传/下载
        }
        else if(buf[0] == '4')
        {
            zt();
        }
        else if(buf[0] == '5')
        {
            break;
        }
        else if(buf[0] == '6')
        {
            exit(0);
        }

        
    }
}

void zt(void)
{

    char buf[256];
    while(1)
    {
        system("clear");
        printf("-------状态-------\n\n");
        // zx();


        printf("1------在线-------\n");
        printf("2------隐身------\n");
        printf("请输入你的选择:");
        
        memset(buf,0,256);
        fgets(buf,256,stdin);
        if(strlen(buf) > 2)
        {
            continue;
        }

        if(buf[0] == '1')
        {
                                  
            memset(sen.message,0,256);
            fgets(sen.message,256,stdin);
            sen.message[strlen(sen.message)-1] = '\0';
            
    
        }
        else if(buf[0] == '2')
        {

        }
    }
}


void zx(void) //获取在线用户列表
{
    return ;
}

void sl(void)
{
    char buf[256];
    char name[256];
    while(1)
    {
        system("clear");
        printf("-------好友在线列表-------\n\n");
        // zx();


        printf("1------选择好友-------\n");
        printf("2-----返回上一层------\n");
        printf("3-------注销---------\n");
        printf("4--------退出---------\n\n");
        printf("请输入你的选择:");
        
        memset(buf,0,256);
        fgets(buf,256,stdin);
        if(strlen(buf) > 2)
        {
            continue;
        }

        if(buf[0] == '1')
        {
            printf("请输入好友名字:");
                        
            memset(name,0,256);
            fgets(name,256,stdin);
            name[strlen(name)-1] = '\0';
            
            hy(name);
        }
        else if(buf[0] == '2')
        {
            break;
        }
        else if(buf[0] == '3')
        {
            
        }
        else if(buf[0] == '4')
        {
            exit(0);
        }
        
    }
}

void hy(char name[])
{
    char buf[256];
    while(1)
    {
        system("clear");
        printf("--------------------\n");
        printf("1-----聊天---------\n");
        printf("2-----查看聊天记录-----\n");
        printf("3------返回上一层-----\n");
        printf("4-------注销--------\n");
        printf("5------退出--------\n");
        printf("---------------\n");

        printf("请输入你的选择:");
        
            
        memset(buf,0,256);
        fgets(buf,256,stdin);
        if(strlen(buf) > 2)
        {
            continue;
        }

        if(buf[0] == '1')
        {
            lt(name);
        }
        else if(buf[0] == '2')
        {
            //打开文件名字叫name和username
        }
        else if(buf[0] == '3')
        {
            break;
        }
        else if(buf[0] == '4')
        {
            //返回登录界面
        }
        else if(buf[0] == '5')
        {
            exit(0);
        }
        
    }
}

void lt(char name[])
{
    sen.pro = 3;
    memset(sen.message,0,256);
    strcpy(sen.message,name);
    send(fd,&sen,len_data,0);

    printf("请求中.....\n");
    sleep(1);

    if(strcmp(rec.message,"OK") == 0)
    {
        printf("对方同意了你的请求....\n");
        printf("......聊天中......\n\n");
        flag = 0;
        sen.pro = 4;
        while(1)
        {
            if(flag)
            {
                printf("对方退出了聊天\n");
                break;
            }
            
            memset(sen.message,0,256);
            fgets(sen.message,256,stdin);
            sen.message[strlen(sen.message)-1] == '\0';  
            send(fd,&sen,len_data,0);
                    
            if(strcmp(sen.message,"MT") == 0)
            {
                break;
            }
        }
        flag = 0;
    }
    else
    {
        printf("%s\n",rec.message);
        printf("\n\n按任意键返回...\n");
        getchar();
    }
}


void ql(void)
{
    char buf[256];
    while(1)
    {
        sen.pro = 2;
        system("clear");
        printf("---群聊----\n\n");
        printf("-------------------\n");
        printf("1------加入群组-------\n");
        printf("-----加入私密群----\n");
     //   printf("---------创建私密群----\n")
        printf("3------返回上一层-------\n");
        printf("4-------注销-------\n");
        printf("5-------退出-------\n");
        printf("-------------------\n\n");

        printf("请输入你的选择:");
        memset(buf,0,256);
        fgets(buf,256,stdin);
        if(strlen(buf) > 2)
        {
            continue;
        }
        if(buf[0] == '1')
        {
            qz();
        }
        else if(buf[0] == '2')
        {
            smq();
        }
        else if(buf[0] == '3')
        {
            break;
        }
        else if(buf[0] == '4')
        {
            
        }
        else if(buf[0] == '5')
        {
            exit(0);
        }
        
    }
}

void smq(void)
{
    
}


int qrs(void)//获取群聊人数
{
    return 0;
}


void qz(void)//应该有获取群人数
{
    sen.pro = 5;
    printf("正在加入.......\n");
    sleep(1);
    send(fd,&sen,len_data,0);
    printf("\n--------群聊中-------\n");
    while(1)
    {     
        memset(sen.message,0,256);
        fgets(sen.message,256,stdin);
        sen.message[strlen(sen.message)-1] == '\0';  
            
        if(strcmp(sen.message,"MT") == 0)
        {
            break;
        }

        send(fd,&sen,len_data,0);
    }
} 
