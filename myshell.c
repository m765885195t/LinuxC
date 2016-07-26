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

void ml(void);

int main(){

    
    //长度不够会引起缓存溢出 
    // while(1){

        printf("mshell:");  
        //不加换行留在缓冲区?
        //解析输入的命令 

        ml();
    
        //为什么1不出来2也就不出来
        //而shell加个换行符就不出来了

  //  }
    return 0;

}

//解析输入的命令
void ml(void){
        
    char a[256],*p,*b[256];
    int i=0,j=0,k,n,t;

    fgets(a,sizeof(a),stdin);
    
    if(strlen(a)>=256)
    {
        printf("输入字过长,退出程序");
        exit(-1);
    }
    
    a[strlen(a)-1]='\0';
    n=1;
    while(1)
    {
        for(i=0,k=0,t=0;a[i];i++)
        {
            if(a[i]==' ')
            {
                if(i>k)
                {
                    t++;
                    k=i;

                }   
            }
        }

        if(t)
        {
            p=(a+k+1);
        }
        else
        {
            p=a;
        }

        printf("%s\n",p);
        b[t]=p;

        
        if(t) //防止将第一个字符串清零
        {
            a[k]='\0';
        }

        if(n)
        {
            n--;
            b[t+1]=NULL;
        }
        if(t==0)
        {
            break;
        }
    }
    
    printf("1%s%s%s\n",b[0],b[1],b[2]);
    //最后一定要加上NULL;

    int stat_val;
    pid_t pid;

    pid=fork();

    if(pid<0)
    {
        printf("创建进程失败;");
        exit(-1);
    }

    if(pid==0)
    {
        execvp(b[0],b);   //子进程执行其他程序
        exit(1);
    }

    if(pid>0)
    {
        wait(&stat_val);   
        
        //父进程等待中
        if(WIFEXITED(stat_val))
        {
            printf("执行成功");
        }
        else
        {
            printf("异常退出");
            exit(0);
        }
    }
}


