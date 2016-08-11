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
#include<time.h>
#include<fcntl.h>
#include<sys/stat.h>

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
    char time[20];
    int pro; //1注册2登录3请求聊天4聊天5群聊6状态
}rec,sen;

int fd;
int flag;

int len_data = sizeof(struct data_info);


void MAIN(void);
void denglu(void);
void zhuce(void);
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
void jianyi(void);
void tm(char a[]);


int main()
{
    struct sockaddr_in ser_addr;
    int len_addr = sizeof(struct sockaddr_in);

    memset(&ser_addr,0,len_addr);
    ser_addr.sin_family = AF_INET;
    ser_addr.sin_port = htons(4567);
    inet_aton("192.168.30.192",&ser_addr.sin_addr);
    //inet_aton("127.0.0.1",&ser_addr.sin_addr);

    fd = socket(AF_INET,SOCK_STREAM,0);

    if(connect(fd,(struct sockaddr *)&ser_addr,sizeof(struct sockaddr_in)) < 0)
    {
        printf("连接失败\n");
        printf("1-请检查网络是否连接\n");
        printf("2-服务器已关,详情咨询<765885195>\n");
        exit(0);
    }

    pthread_t p_t;
    pthread_create(&p_t,NULL,session,NULL);

    MAIN();
}


void *session(void *a)
{
    char b[100][1000];
    int i;
    while(1)//未读消息功能
    {
        recv(fd,&rec,len_data,0);

        if(rec.pro == 4)
        {
            char buf[128];
            FILE *fp;
            sprintf(buf,"%s%s%s%s",".MT",rec.Y_name,"|",rec.I_name);
            fp = fopen(buf,"a");
            fwrite(&rec,len_data,1,fp);
            fclose(fp);
            
            if(sen.pro == 4)
            {
                if(strcmp(rec.message,"MT") != 0)
                {   
                    printf("%s >>> %-30s%s\n",rec.I_name,rec.message,rec.time);
                } 
                else
                {
                    printf("对方退出了聊天\n");
                }

            }       
        }
        if(sen.pro == 5)
        {   
           printf("%s >>> %-30s%s\n",rec.I_name,rec.message,rec.time);
        }
        if(sen.pro == 6)
        {
            printf("当前状态为:%s\n\n",rec.message);
        }
        if(sen.pro == 7)
        {
            printf("%s\n",rec.message);
        }
    }
}

void MAIN(void)
{
    char buf[256];

    while(1)
    {
        sen.pro = 0;
        system("clear");
        printf("---------------\n");
        printf("------MT-----\n");
        printf("---------------\n");
        printf("1----登录------\n");
        printf("2----注册------\n");
        printf("3---忘记密码----\n");
        printf("4----使用说明-----\n");
        printf("5---建议反馈-----\n");
        printf("6----退出------\n");
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
            printf("\n按任意键继续.....\n");
            getchar();
        }
        else if(buf[0] == '4')
        {
            system("clear");
            system("cat MT");
            printf("\n按任意键返回...\n");
            getchar();

        }
        else if(buf[0] == '5')
        {
            jianyi();
        }
        else if(buf[0] == '6')
        {
            sen.pro = 6;
            strcpy(sen.message,"MT");
            send(fd,&sen,len_data,0);
            exit(0);            
        }
    }
}

void tm(char a[])
{
    time_t nowtime;
    struct tm* timeinfo;
    time(&nowtime);

    timeinfo = localtime(&nowtime);

    strncpy(a,asctime(timeinfo),19);
    a[19] = '\0';
}

void jianyi(void)
{
    char buf[256];
    while(1)
    {
        sen.pro = 10;
        system("clear");
        printf("1----建议------\n");
        printf("2----返回主界面------\n\n");
        
        printf("请输入你的选择:");
        memset(buf,0,256);
        fgets(buf,256,stdin);
        if(strlen(buf) > 2)
        {
            continue;
        }
        if(buf[0] == '1')
        {
            printf("建议:");
            memset(sen.message,0,256);
            fgets(sen.message,256,stdin);
            sen.message[strlen(sen.message)-1] = '\0';
            send(fd,&sen,len_data,0);
            printf("\n\n提交中.....\n");
            sleep(1);
            printf("感谢你的建议\n");
            break;
        }
        else if(buf[0] == '2')
        {
            break;
        }
    }
}

void denglu(void)
{
    for(int i=0;i<3;i++)
    {
        sen.pro = 0;
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
            memset(rec.message,0,256);
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
    int id,i;
    sen.pro = 1;

    for(i=0;i<3;i++)
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
            sleep(1);
        }
        else 
        {
            printf("两次密码输入不一致...\n");
            sleep(1);
            continue;
        }
        if(strcmp(rec.message,"1") == 0)
        {
            printf("\n注册成功...\n");
            sleep(1);
            break;
        }
        if(strcmp(rec.message,"0") == 0)
        {
            printf("\n用户名重名.\n");
            sleep(1);
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
        printf("---欢迎进入MT----\n\n");
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
            sen.pro = 6;
            strcpy(sen.message,"ZX");
            send(fd,&sen,len_data,0);
            MAIN(); 
        }
        else if(buf[0] == '6')
        {
            sen.pro = 6;
            strcpy(sen.message,"MT");
            send(fd,&sen,len_data,0);
            exit(0);
        }

        
    }
}

void zt(void)
{

    char buf[256];
    while(1)
    {
        sen.pro = 6;
        system("clear");
        printf("-------状态-------\n\n");
       
        
        memset(sen.message,0,256);
        strcpy(sen.message,"ZT");
        send(fd,&sen,len_data,0);
        sleep(1);

        printf("\n请选择你要修改的状态:\n");

        printf("1------在线-------\n");
        printf("2------隐身------\n");
        printf("3------返回上一层-----\n\n");
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
            strcpy(sen.message,"1");
            send(fd,&sen,len_data,0);
        }
        else if(buf[0] == '2')
        {
            memset(sen.message,0,256);
            strcpy(sen.message,"2");
            send(fd,&sen,len_data,0);
        }
        else if(buf[0] == '3')
        {
            break;
        }

    }
}

void sl(void)
{
    char buf[256];
    char name[256];
    while(1)
    {
        system("clear");
        printf("-------好友在线列表-------\n\n");
        
        sen.pro = 7;
    
        memset(sen.message,0,256);
        send(fd,&sen,len_data,0);
    
        sleep(1);
        sen.pro = 2;
        printf("\n1------选择好友-------\n");
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
            if(strcmp(USER.username,name) == 0)
            {
                printf("好友对象不能为自己\n");
                sleep(1);
                continue;
            }

            hy(name);
        }
        else if(buf[0] == '2')
        {
            break;
        }
        else if(buf[0] == '3')
        {
            sen.pro = 6;
            strcpy(sen.message,"ZX");
            send(fd,&sen,len_data,0);
            MAIN();  
        }
        else if(buf[0] == '4')
        {
            sen.pro = 6;
            strcpy(sen.message,"MT");
            send(fd,&sen,len_data,0);
            exit(0);
        }
        
    }
}

void hy(char name[])
{
    char buf[256];
    while(1)
    {
        sen.pro = 3;
        system("clear");
        printf("--------------------\n");
        printf("1-----与他(她)聊天---------\n");
        printf("2-----聊天记录(含未读消息)-----\n");
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
            system("clear");
            printf("--------聊天记录--------\n\n");
            FILE *fp;
            char buf[128];
            struct data_info buff;
            sprintf(buf,"%s%s%s%s",".MT",USER.username,"|",name);
            fp = fopen(buf,"r");
            while(fread(&buff,len_data,1,fp) > 0)
            {
                printf("%s >>> %-30s%s\n",buff.I_name,buff.message,buff.time);
            }
            printf("\n\n请按任意键返回...\n");
            getchar();
        }
        else if(buf[0] == '3')
        {
            break;
        }
        else if(buf[0] == '4')
        {
            sen.pro = 6;
            strcpy(sen.message,"ZX");
            send(fd,&sen,len_data,0);
            MAIN();
        }
        else if(buf[0] == '5')
        {
            sen.pro = 6;
            strcpy(sen.message,"MT");
            send(fd,&sen,len_data,0);
            exit(0);
        }
        
    }
}

void lt(char name[])
{
    char *p;
    memset(sen.message,0,256);
    strcpy(sen.Y_name,name);
    send(fd,&sen,len_data,0);

    printf("请求中.....\n");
    sleep(1);

    if(strcmp(rec.message,"OK") == 0)
    {
        system("clear");
        printf("......聊天中......\n\n");
        flag = 0;
        sen.pro = 4;
        FILE *fp;
        char buf[128];
        sprintf(buf,"%s%s%s%s",".MT",sen.I_name,"|",sen.Y_name);
        while(1)
        {   
            memset(sen.message,0,256);
            tm(sen.time);
    
            fgets(sen.message,256,stdin);
            sen.message[strlen(sen.message)-1] = '\0';          
            send(fd,&sen,len_data,0);
            if(strcmp(sen.message,"MT") == 0)
            {
                break;
            }
                
            fp = fopen(buf,"a+");
            fwrite(&sen,len_data,1,fp);
            fclose(fp);
        }
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
        printf("2-----查看群聊天记录-----\n");
      //  printf("-----加入私密群----\n");
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
            system("clear");
            printf("--------群聊天记录--------\n\n");
            FILE *fp;
            struct data_info buff;
            fp = fopen(".MTqunzu","r");
            while(fread(&buff,len_data,1,fp) > 0)
            {
                printf("%s >>> %-30s%s\n",buff.I_name,buff.message,buff.time);
            }
            printf("\n\n请按任意键返回...\n");
            getchar();
        }
        else if(buf[0] == '3')
        {
            break;
        }
        else if(buf[0] == '4')
        {
            sen.pro = 6;
            strcpy(sen.message,"ZX");
            send(fd,&sen,len_data,0);
            MAIN();
        }
        else if(buf[0] == '5')
        {
            sen.pro = 6;
            strcpy(sen.message,"MT");
            send(fd,&sen,len_data,0);
            exit(0);
        }
        
    }
}

void smq(void)
{
    
}


void qz(void)
{
    sen.pro = 5;
    printf("正在加入.......\n");
    sleep(1);
    system("clear");
    send(fd,&sen,len_data,0);
    printf("\n--------群聊中-------\n");
    while(1)
    {     
        memset(sen.message,0,256);
        fgets(sen.message,256,stdin);
        sen.message[strlen(sen.message)-1] = '\0';  
        send(fd,&sen,len_data,0);

        if(strcmp(sen.message,"MT") == 0)
        {
            break;
        }
    }
} 
