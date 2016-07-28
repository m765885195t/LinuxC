/*************************************************************************
	> File Name: mshell.c
	> Author:motian 
	> Mail:765885195@qq.com 
	> Created Time: 2016年07月25日 星期一 16时54分32秒
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<string.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>
#include<fcntl.h>
#include<dirent.h>                //后台有问题
#include<sys/stat.h>              // 修改函数名
#include<signal.h>
#include<stdio_ext.h>

void shell(void);
void f(int);

void f(int signum) //接收到终止信号时的处理
{    
    printf("\n");
}

//解析命令并执行程序
void shell(void)
{
    
    char a[256],*b[100],*c[100];   //a输入命令   b命令表
    int i,j,k,t,n=1,x=0,fd,z=0,fd1;
    pid_t pid,pid2;
    int stat_val,stat_val1;
    int pipefd[2];
    char ch;
    
    memset(a,0,256);

    fgets(a,sizeof(a),stdin);  //输入命令
    
    a[strlen(a)-1]='@';            //清'\n'

    fd1=open("/home/motian/linuxC/fork/h",O_CREAT|O_WRONLY|O_APPEND);                      
    write(fd1,a,strlen(a));                 //为什么历史命令加不了
    close(fd1);

    a[strlen(a)-1]='\0';

    while(1)
    {
        for(i=0,k=0,t=0;a[i];i++)
        {
            if(a[i]==' ')    //目前不处理多个空格的
            {
                if(i>k)
                {
                    t++;
                    k=i;
                }    
            }
        }
    
        if(n)
        {
            n--;
            b[t+1]=NULL;        //换一种方法
        }
        
        if(t)
        {
            b[t]=(a+k+1);
            a[k]='\0';  
        }
        else
        {
            b[t]=a;
            break;
        }
    }

    i=0;
    
    while(b[i]!=NULL)
    {
        if(x!=1 && x!=2 && strcmp(b[i],"|")==0 )
        {
            x=4;
            j=0;
            b[i++]=NULL;
            while(b[i]!=NULL)
            {
                c[j++]=b[i++];
            }
            c[j]=NULL;
            break;
        }
        
        if (x!=2  && strcmp(b[i],">")==0)
        {
           fd=creat(b[i+1],0644);
            x=1;
            b[i]=NULL;
            break;
        }
    
        if(x!=1 && strcmp(b[i],"<")==0)
        {
            fd=open(b[i+1],O_RDONLY);
            x=2;
            b[i]=NULL;
            break;
        }
        if(x!=1 && x!=2 && strcmp(b[i],"&")==0 )
        {
            x=3;
            b[i]=NULL;
        }

        i++;
    }
    
    if(!strcmp(b[0],"exit") || !strcmp(b[0],"logout"))
    {
        exit(0);
    }
    
    //检查命令
   /*
   char *path[]={"./","/usr/bin","/bin",NULL};
    int g=0,flag=0;
    DIR* dp;
    struct dirent* dirp;

    while(path[g]!=NULL)
    {
        dp=opendir(path[g]);
        while( (dirp = readdir(dp) ) != NULL)
        {
            if( strcmp(dirp->d_name,b[0])==0)
            {
                closedir(dp);
                flag=1;
            }
        }
        g++;
    }

    if(!flag)                 //回车符的判断
    {
        printf("没有此命令\n");
        return ;
    }

   */

    //命令
//-------------------------------------------
    //执行
    pid=fork();

    if(pid<0)
    {
        printf("创建进程失败\n");
        exit(-1);
    }
    
    if(pid==0)
    {
        if(x==1)            //>
        {
            dup2(fd,1);
            execvp(b[0],b);
        }
        else if(x==2)         //<
        {
            dup2(fd,0);
            execvp(b[0],b);
        }
        
        else if(x==4) //管道
        {
            
            pipe(pipefd);
            pid2=fork();

            if(pid2>0)
            {
            
                waitpid(pid2,&stat_val1,0);      
                close(pipefd[1]);      //先关写端
                dup2(pipefd[0],0);     //重定向读端到标准输入流
                execvp(c[0],c);
            }

            if(pid2<0)
            {
                printf("进程创建失败\n");
            }

            if(pid2==0)
            {
                close(pipefd[0]);     //先关读端
                dup2(pipefd[1],1);    //重定向写端到标准输出流
                execvp(b[0],b);  
            }
        }

        else
        {
            execvp(b[0],b); 
        }

        exit(0);
    }

    if(pid>0)
    {
        if(!(x==3))     //后台等
        {    
            waitpid(pid,&stat_val,0);     
        }
    }
}


//主函数
int main()
{
    while(1)
    {
        signal(SIGINT,f);
        printf("\33[7mmotian\033[0m:");
        shell();
        fflush(stdin);
    }
}
