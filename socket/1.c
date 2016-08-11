/*************************************************************************
	> File Name: 1.c
	> Author: 
	> Mail: 
	> Created Time: 2016年08月10日 星期三 22时00分04秒
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
int main()
{
    system("gcc servsr4.c -o servsr4 -lpthread");
    usleep(1);
    system("gcc client4.c -o client4 -lpthread");
}
