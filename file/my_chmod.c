//改变文件访问权限       //输入真的只取后三位的八进制？
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>

int main(int argc,char *argv[])
{	
	int mode;     //改变量用来保存用户输入的权限
	int mode_u;    //文件拥有者的权限

	int mode_g;    //拥有者所属组的权限
	
	int mode_o;    //其他用户的权限
	
	char *path;
	
	if(argc<3)
	{
	printf("输入有误，参数输入至少为三个");
	exit(0);
	}
	
	mode=atol(argv[1]);
	
	/*if(mode>777||mode<0)
	{
		printf("权限输入有误");
		exit(0);	
	}*/
	
	mode_u=mode/100;
	mode_g=mode%100/10;
	mode_o=mode%10;
	mode=mode_u*64+mode_g*8+mode_g;
	path=argv[2];
	
	if(chmod(path,mode)==-1)
	{
		printf("权限更改失败");
	}
	else
	{
		printf("权限更改成功");
	}
}
