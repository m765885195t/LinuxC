#include<stdio.h>
#include<error.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
/*读数据函数*/

int my_read(int fd)
{
	int  len;
	int  ret;
	int i;
	char read_buf[64];
	
	/*获取文件长度*/
	
	if(lseek(fd,0,2)==-1)
		printf("文件指针定位失败");
	if((len=lseek(fd,0,1))==-1)
		printf("文件指针定位失败");
	if(lseek(fd,0,0)==-1)
		printf("文件指针定位失败");
	
	printf("文件大小为:%d",len);
		
	if(!(ret=read(fd,read_buf,len)))
		printf("文件读写成功,内容如下:\n%s",read_buf);
	return ret;
}

int main()
{
	int fd;
	char write_buf[32]="hello world!";
	
	if((fd=creat("1.c",S_IRWXU))==-1)
		printf("文件创建失败");
	else
		printf("文件创建成功");
	
	if(write(fd,write_buf,strlen(write_buf))!=strlen(write_buf))
		printf("文件写不成功");
	
	my_read(fd);
	
	//演示文件
	
	printf("-----------------");
	if(lseek(fd,10,2)==-1)
		printf("文件指针定位失败");
	if(write(fd,write_buf,strlen(write_buf))!=strlen(write_buf))
		printf("文件写不成功");		
		
	my_read(fd);	
	printf("-----------------");
	close(fd);
	return 0;
}
