#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<error.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
int main()
{
	int f;
	//if((f=open("t.c",O_CREAT|O_EXCL,S_IRUSR|S_IWUSR))==-1){
	if((f=creat("t.c",S_IRWXU))==-1){
			//perror("open");
			//printf("打开:%s     错误:%d\n",strerror(errno),errno);
			exit(1);
		}
	else
		printf("成功创建文件\n");
	close(f);
	return 0;
}
