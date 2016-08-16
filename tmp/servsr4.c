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
#include<fcntl.h>
#include<dirent.h>

struct user_info{          //用户信息结构体
//    long ID;//MT号
    char username[32];
    char password[16];
    int fd;
    int man;
    int state;//0离线1在线2隐身3正在聊天   状态
    int vip;

                 //    char autograph[:w256];
}USER[50],*USERp;


struct data_info{       //私聊消息结构体
    char I_name[32];
//    long I_ID;    
    char Y_name[32];
//    long Y_ID;      
    char message[256];
   char time[20];
    int pro;//1注册2登录3请求4聊天5群聊6修改状态7好友在线表8改密9上传文件10下载文件11下载文件列表12升级vip13创建私密群
};

struct ql_info{              //群聊信息结构体
    int fd;
    char message[256];
    char I_name[32];
//    long ID;
    int man;
}cy[50],*cyp;

struct file_info
{
    char name[128];
}wj[100];


int len_data = sizeof(struct data_info);
int num;

struct smqcy{
    int fd;
    char name[32];
    int man;
};

struct smq_info{
    char name[32];
    char pass[32];
    int man;
    struct smqcy cyname[30];
}smq[30];


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
    memset(USER,0,sizeof(struct user_info)*50);
    memset(USER,0,sizeof(struct smq_info)*30);
    USER[0].man = 1;
    strcpy(USER[0].username,"MT");
    strcpy(USER[0].password,"765885195"); //MT
    USER[0].state = 1;
    USER[0].vip = 1;
    strcpy(cy[0].I_name,"MT");
    cy[0].man = 1;
  
    FILE *fp;
/*    fp = fopen("/home/motian/linuxC/socket/.MT/smq","r");
    for(int i=0;i<30;i++)
    {
        fread(&smq[i],sizeof(struct smq_info),1,fp);
    }
    fclose(fp);
*/

    fp = fopen("/home/motian/linuxC/socket/.MT/USER","r");
    for(int i=1;i<50;i++)
    {
        fread(&USER[i],sizeof(struct user_info),1,fp);
        printf("|%s:%s:%d|",USER[i].username,USER[i].password,USER[i].vip);
    }
    fclose(fp);
    
    printf("\n");
    
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

int z;
void * session(void *a)
{
    int fd = *(int *)a;
    struct data_info sen,rec;
    int i;
    int b;

    while(1)
    {
        b=recv(fd,&rec,len_data,0);
        if(b==0)
        {
            if((USERp = find(rec.I_name)) != NULL)
            {
                if(USERp->fd == fd)
                {
                    USERp->state = 0;
                    printf("%s异常下线\n",rec.I_name);
                }
                close(fd);
                pthread_exit(NULL);
            }
        }
        if(rec.pro == 1)
        {
            int flag = 0;
            int t = 0;
            puts("注册");

            for(i=1;i<50;i++)
            {
                if(strcmp(rec.I_name,USER[i].username) == 0)
                {
                    t = 1;
                }
            }
            if(!t)
            {
                
                for(i=1;i<50;i++)
                {
                    if(USER[i].man == 0)
                    {
                        USER[i].man = 1;
                        flag = 1; 
                        strcpy(USER[i].username,rec.I_name);
                        strcpy(USER[i].password,rec.Y_name);

                        memset(sen.message,0,256);
                        strcpy(sen.message,"1");
                        send(fd,&sen,len_data,0);
                        printf("账号:%s,密码:%s\n",USER[i].username,USER[i].password);
                        
                        FILE *fp;
                        fp = fopen("/home/motian/linuxC/socket/.MT/USER","a");
                        
                        fwrite(&USER[i],sizeof(struct user_info),1,fp);
                        fclose(fp);
                        break;
                    }
                }
            }
            else
            {
                memset(sen.message,0,256);
                strcpy(sen.message,"0");
                send(fd,&sen,len_data,0);
            }
         
        }
        if(rec.pro == 2)
        {
            puts("登录");
            int flag = 0;
            for(i=1;i<50;i++)
            {
                if((USER[i].man == 1) && (USER[i].state == 0))
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
                memset(sen.message,0,256);
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
                strcpy(sen.message,"OK");
                send(fd,&sen,len_data,0);
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
            
            sen.pro = 4;
            strcpy(sen.message,rec.message);
            strcpy(sen.Y_name,rec.Y_name);//转发消息
            strcpy(sen.I_name,rec.I_name);
            strcpy(sen.time,rec.time);
            send(USERp->fd,&sen,len_data,0);
        }

        if(rec.pro == 5)
        {
            char s[2];
            int flag = 0;
            puts("群聊中");
            for(i=0;i<50;i++)
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
                    num++;
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
                strcpy(sen.I_name,rec.I_name);
                sprintf(s,"%d",num);
                s[strlen(s)]='\0';
                sprintf(sen.message,"%s%d%s","加入了群组,群聊人数共",num,"人\n");
                
            }
            else
            {
                if(strcmp(rec.message,"MT") == 0)
                {
                    strcpy(sen.I_name,rec.I_name);
                    sprintf(sen.message,"%s%d%s","退出了群组,群聊人数共",num-1,"人");
                    cyp = find2(rec.I_name);
                    cyp->man = 0;
                    num-- ;
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
            
            if((strcmp(rec.message,"MT") == 0) && ((USERp->state == 1) || (USERp->state == 2 )))
            {
                USERp->state = 0;
                printf("%s下线了\n",USERp->username);
                
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
            int k = 1;
            for(i=1;i<50;i++)
            {
                if(USER[i].state == 1)
                {
                
                    sprintf(s,"%d",k);
                    s[strlen(s)]='\0';
                    memset(sen.message,0,256);
                    sprintf(sen.message,"%s%s%s",s," >     ",USER[i].username);
                    send(fd,&sen,len_data,0);
                    k++;
                }
            }
        }
        if(rec.pro == 8)
        {
            
            FILE *fp;
            struct user_info buf;
            int flag = 0; 
          
            fp = fopen("/home/motian/linuxC/socket/.MT/USER","w+");
            for(i=1;i<50;i++)
            {
                if(strcmp(USER[i].username,rec.I_name) == 0)
                {
                    if(strcmp(USER[i].password,rec.Y_name) == 0)
                    {
                        memset(USER[i].password,0,32);
                        strcpy(USER[i].password,rec.message);
                    
                        memset(sen.message,0,256);
                        strcpy(sen.message,"1");
                        send(fd,&sen,len_data,0);
                        USER[i].man = 1;
                        USER[i].state = 1;
                        buf = USER[i];
                        flag = 1;
                    }
                }
                
                if(flag)
                {
                    fwrite(&buf,sizeof(struct user_info),1,fp);
                    fclose(fp);
                    break;
                }
                fread(&buf,sizeof(struct user_info),1,fp);
            }
            if(!flag)
            {
                memset(sen.message,0,256);
                strcpy(sen.message,"2");
                send(fd,&sen,len_data,0);
                fclose(fp);
            }
        }
        if(rec.pro == 9)
        {
            char buf[256];
            USERp = find(rec.I_name);
            FILE *fp;

            memset(buf,0,256);
            sprintf(buf,"%s%s","/home/motian/linuxC/socket/.MT/xiazai/",rec.Y_name);
            fp = fopen(buf,"a+");
            if(fp != NULL)
            {
                if(USERp->vip != 1)
                {
                    fwrite(rec.message,1,1,fp);
                }
                else
                {
                    fwrite(rec.message,2,1,fp);
                }
            }
            fclose(fp);
        }
        if(rec.pro == 10)
        {
            puts("下载中");
            int t = 0;
            char buf[128];
            
            USERp = find(rec.I_name);
            t=atoi(rec.message);

            sen.pro = 10; 
            memset(sen.Y_name,0,32);
            memset(sen.message,0,256);
            strcpy(sen.message,"name");
            
            printf("%s在下载%s\n",rec.I_name,wj[t-1].name);

            strcpy(sen.Y_name,wj[t-1].name);
            send(fd,&sen,len_data,0);
            sleep(3);

            sprintf(buf,"%s%s","/home/motian/linuxC/socket/.MT/xiazai/",wj[t-1].name);
            
            FILE *fp;
            sen.pro = 10;
            
            if((fp = fopen(buf,"r")) != NULL)
            {
                while(1)
                {
                    if(fread(sen.message,2,1,fp) <1)
                    {
                        fclose(fp);
                        break;
                    }
             
                    send(fd,&sen,len_data,0);
                }
            }
            else
            {
                perror("fopen");
                fclose(fp);
            }
        }
    
        if(rec.pro == 11)
        {
            DIR *dir;
            int i=0;
            struct dirent *w;
            dir = opendir("/home/motian/linuxC/socket/.MT/xiazai/");
        
            while((w=readdir(dir)) != NULL) 
            {
                if((strcmp(w->d_name,".") == 0) || (strcmp(w->d_name,"..") ==0))
                {
                    continue;
                }
                strcpy(wj[i].name,w->d_name);
                sprintf(sen.message,"%d%s%s",i+1,">>",wj[i].name);
                send(fd,&sen,len_data,0);
                i++;
            }
            closedir(dir);
        }
        if(rec.pro == 12)
        {
            if((USERp = find(rec.I_name)) != NULL)
            {
                USERp->vip = 1;
            }            
        }
        if(rec.pro == 13)   //创建私密群
        {  
            USERp = find(rec.I_name);

            struct smq_info buf;
            memset(&buf,0,sizeof(struct smq_info));
            strcpy(buf.name,sen.message);
            strcpy(buf.pass,sen.Y_name);
            buf.man = 1;
            buf.cyname[0].fd = USERp->fd;
            strcpy(buf.cyname[0].name,rec.I_name);
            buf.cyname[0].man = 1;

            FILE *fp;
            int flag = 0;
            fp = fopen("/home/motian/linuxC/socket/.MT/smq","a+");    
            for(i=0;i<30;i++)
            {
                if(smq[i].man == 1)
                {
                    if(strcmp(sen.message,smq[i].name) == 0)
                    {
                        flag = 1;
                    }
                }
            }
            if(!flag)
            {  
                fwrite(&buf,sizeof(struct smq_info),1,fp);
                memset(sen.message,0,256);
                strcpy(sen.message,"1");
                send(fd,&sen,len_data,0); 
            }
            else 
            {
                memset(sen.message,0,256);
                strcpy(sen.message,"2");
                send(fd,&sen,len_data,0); 
            }
            fclose(fp);
        }
        if(rec.pro == 14)
        {
            for(i=0;i<30;i++)
            {
                if(smq[i].man == 1)
                {
                    memset(sen.message,0,256);
                    strcpy(sen.message,smq[i].name);
                    send(fd,&sen,len_data,0);
                }   
            }
        }
    }
}


