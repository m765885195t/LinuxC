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
#include<dirent.h>                
#include<sys/stat.h>              // 修改函数名
#include<signal.h>
#include<stdio_ext.h>

char his_command[256];

void history(void)        //历史记录
{
    int fd,len,i;
    char *p,his[120];
    static int number=1;

    fd=open("/home/motian/linuxC/fork/.myshellhistory",O_RDONLY);

    read(fd,&his,120);

    len=strlen(his);

    p=his;

    for(i=0;i<len;i++)
    {
        if(his[i]=='+')
        {
            his[i]='\0';
            printf("%d  ",number);
            printf("%s\n",p);
            p=his+1+i;
            number++;
        }
    }
}

//解析命令并执行程序
void shell(void)
{
    
    char in_order[256];
    char *par_order[100];           //解析命令
    char *pipe_order[100];
    char  option='\0';     //接受选项 > < | &
  
    int number,len_order;  
    int i,j,k;

    memset(in_order,0,256);
    
    /*
    char ch;
    if((ch=getchar())==65)
    {
        printf("上键\n");
        return ;
    }
    */

    fgets(in_order,sizeof(in_order),stdin);  //输入命令
    

    if(in_order[0]=='\n')
    {
        return ;
    }
    
    
   // if(strcmp(in_order,"^[[A")==0)
   //     printf("\b")


    len_order=strlen(in_order);

    
    int historyfd;
    in_order[len_order-1]='+';         

    historyfd=open("/home/motian/linuxC/fork/.myshellhistory",O_CREAT|O_WRONLY|O_APPEND,0666);                      
    write(historyfd,in_order,len_order);                 //为什么历史命令加不了
    close(historyfd);
    

    in_order[len_order-1]='\0';

    int n=1;
    while(1)
    {
        for(i=0,k=0,number=0;in_order[i];i++)
        {
            if(in_order[i]==' ')    //目前不处理多个空格的
            {
                if(i>k)
                {
                    number++;
                    k=i;
                }    
            }
        }
    
        if(n)
        {
            n--;
            par_order[number+1]=NULL;        //换一种方法
        }
        
        if(number)
        {
            par_order[number]=(in_order+k+1);
            in_order[k]='\0';  
        }
        else
        {
            par_order[number]=in_order;
            i=0;
            break;
        }
    }
    
    int fd;
    while(par_order[i]!=NULL)
    {
        if( option!='>' && option!='<' && strcmp(par_order[i],"|")==0 )
        {
            option='|';
            j=0;
            par_order[i++]=NULL;
            while(par_order[i]!=NULL)
            {
                pipe_order[j++]=par_order[i++];
            }
            pipe_order[j]=NULL;
            break;
        }
        
        if (option!='<' && strcmp(par_order[i],">")==0)
        {
           fd=creat(par_order[i+1],0644);
            option='>';
            par_order[i]=NULL;
            break;
        }
    
        if(option!='>' && strcmp(par_order[i],"<")==0)
        {
            fd=open(par_order[i+1],O_RDONLY);
            option='<';
            par_order[i]=NULL;
            break;
        }
        if(option!='>' && option!='<' && strcmp(par_order[i],"&")==0 )
        {
            option='&';
            par_order[i]=NULL;
        }

        i++;
    }
    
    if(!strcmp(par_order[0],"history"))
    {
        history();
        return ;
    }
    if(!strcmp(par_order[0],"exit") || !strcmp(par_order[0],"logout"))
    {
        printf("再见!!!\n");
        exit(0);
    }
    
    if(!strcmp(par_order[0],"cd"))
    {
        int flag=0;
        if(par_order[1]==NULL || !strcmp(par_order[1],"~"))  //cd
        {
            strcpy(his_command,"/home/motian");
            if( chdir("/home/motian") == 0 )
                flag=1;
            return ;
        }
        if( !strcmp(par_order[1],".") || !strcmp(par_order[1],"..") )
        {
            flag=1;
        }
        /*
        if(b[1][0]=='-')
        {
            if( chdir(his_command) == 0 )
                flag=1;                     // cd -实现方法
            return ;
        }
        */
        
        strcpy(his_command,par_order[1]);
        if( chdir(par_order[1]) == 0 )
            flag=1;
        
        if(!flag)
        {
            printf("没有那个文件或目录\n");
        }
        return ;
    }

    //检查命令
    {
        
        char *path[]={"/home/motian/linuxC/fork","/usr/bin","/bin",NULL};
        int g=0,flag=0;
        DIR* dp;
        struct dirent* dirp;

        while(path[g]!=NULL)
        {
            dp=opendir(path[g]);
            while( (dirp = readdir(dp) ) != NULL)
            {
                if( strcmp(dirp->d_name,par_order[0])==0)
                {
                    closedir(dp);
                    flag=1;
                }
            }
            g++;
        }

        if(!flag)           
        {
            printf("没有此命令\n");

        }
    }


//　　　　命令解析
//--------------------------------
//　　　  执行命令


    int stat_val,stat_val1;
    pid_t pid,pid2;

    pid=fork();

    if(pid<0)
    {
        printf("创建进程失败\n");
        exit(-1);
    }
    
    if(pid==0)
    {
        if(option=='>')            //>
        {
            dup2(fd,1);
            execvp(par_order[0],par_order);
            exit(0);
        }
        else if(option=='<')         //<
        {
            dup2(fd,0);
            execvp(par_order[0],par_order);
            exit(0);
        }
        
        else if(option=='|') //管道
        {
            int pipefd[2];

            pipe(pipefd);
            pid2=fork();

            if(pid2>0)
            {  
                waitpid(pid2,&stat_val1,0);      
                close(pipefd[1]);      //先关写端
                dup2(pipefd[0],0);     //重定向读端到标准输入流
                execvp(pipe_order[0],pipe_order);
                exit(0);
            }

            if(pid2<0)
            {
                printf("进程创建失败\n");
                exit(0);
            }

            if(pid2==0)
            {
                close(pipefd[0]);     //先关读端
                dup2(pipefd[1],1);    //重定向写端到标准输出流
                execvp(par_order[0],par_order);  
                exit(0);
            }
        }

        else
        {
            execvp(par_order[0],par_order); 
            exit(0);
        }
    }

    if(pid>0)
    {
        if(!(option=='&'))     //后台等
        {    
            waitpid(pid,&stat_val,0);
            return ;
        }
    }
}

void f(int signal1)
{

}
//主函数
int main()
{

    char dir[256],*p;
    while(1)
    {
        signal(SIGINT,f);
        printf("\033[01;32mmotian\033[0m:");
        getcwd(dir,256);

        if(!strncmp(dir,"/home/motian",12))
        {
            p=dir+12;
            printf("\033[01;34m~%s\033[0m$ ",p);
        } 
        else
        {
            printf("\033[01;34m%s\033[0m$ ",dir);
        }
        
        shell();
    }
}
