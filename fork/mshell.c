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

void zx(char *a[]);
char** ml(void);

int main(int argc,char *argv[]){

    char *b[256];
    
    while(1){
        printf("mshell:");
        //解析输入的命令
    
        zx(ml());


    }
    return 0;

}

//解析输入的命令
char** ml(void){
        
    char a[256],*p,*b[50],*c;
    int i=0,j=0,k,n,t;


    fgets(a,sizeof(a),stdin);
    
    if(strlen(a)>=256){
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

        printf("%s\n",p);
        a[k]='\0';
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

    

    //最后一定要加上NULL;
    return b;
}

//建立新进程,在子进程中执行程序,父挂起
void zx(char *a[]){   //a参数表
    
    int stat_val;
    pid_t pid;

    pid=fork();

    if(pid<0){
        printf("创建进程失败;");
        exit(-1);
    }

    if(pid==0){
        
        if(a[3]!=NULL)
        {
            printf("sss\n");
        }
        execvp(a[0],a);   //子进程执行其他程序
        exit(1);
    }

    if(pid>0){
        wait(&stat_val);            //父进程等待中
        if(WIFEXITED(stat_val)){
            printf("执行成功");
            return ;
        }
        else{
            printf("异常退出");
            exit(0);
        }
    }
    


}

//执行程序

