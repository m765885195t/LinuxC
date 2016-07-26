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
#include<sys/stat.h>

//解析命令并执行程序
void shell(void)
{
        
    char a[256],*b[100];   //a输入命令   b命令表
    int i,j,k,t,n=1;
    pid_t pid;
    int stat_val;

    fgets(a,sizeof(a),stdin);  //输入命令
    
    if(strlen(a)>=256)
    {
        printf("command is too long\n");           //命令输入太长
        exit(-1);
    }
    
    a[strlen(a)-1]='\0';            //清'\n'

    while(1)
    {
        for(i=0,k=0,t=0;a[i];i++)
        {
            if(a[i]==' ')              //多个空格的处理?
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
            b[t+1]='\0';        // 结尾加\0,换一种方法
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
    if(*b[1]=='\0')
    printf("111\n");


    //解析命令
//-------------------------------------------
    //执行程序

    pid=fork();

    if(pid<0)
    {
        printf("创建进程失败\n");
        exit(-1);
    }

    if(pid==0)
    {
        execvp(b[0],b);   //子进程执行其他程序
        exit(0);
    }

    if(pid>0)
    {
        wait(&stat_val);   //父进程等待中
    }
}

//主函数
int main()
{
    while(1)
    {
        printf("motian:");
        shell();
    }
}
