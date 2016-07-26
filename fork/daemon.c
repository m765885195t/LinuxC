/*************************************************************************
	> File Name: daemon.c
	> Author:motian 
	> Mail:765885195@qq.com 
	> Created Time: 2016年07月25日 星期一 10时23分05秒
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<time.h>
#include<signal.h>
#include<sys/stat.h>
#include<syslog.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>

//守护进程
int init_daemon(void){
    
    pid_t pid;
    int i,n=1,fd;
    char *buf="mo tian.\n";

    pid=fork();
    
    if(pid!=0){
        exit(0);
    }

    //他的返回值就是该进程组的ID,也是该进程组长的pid
    setsid();

    chdir("/");

    umask(0);

    for(i=0;i<getdtablesize();close(i));
     
   
    //为什么找不到文件,程序死循环

    while(n--){
        if( (fd=open("/home/moian/1.c",O_CREAT|O_WRONLY|O_TRUNC,S_IRUSR|S_IWUSR))==-1 ){
            printf("打开文件失败");
            exit(1);
        }

        write(fd,buf,strlen(buf)+1);
        close(fd);
        sleep(1);
        printf("111");
    }

    return 0;
}

int main(){
    init_daemon();
}








