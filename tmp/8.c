/*************************************************************************
	> File Name: 8.c
	> Author: 
	> Mail: 
	> Created Time: 2016年08月10日 星期三 15时51分27秒
 ************************************************************************/

#include<stdio.h>
#include<time.h>
#include<string.h>
int main()
{
    time_t nowtime;
    struct tm * timeinfo;
    char buf[256];
    time(&nowtime);

    timeinfo = localtime (&nowtime);

    strncpy(buf,asctime(timeinfo),19);
    buf[19]='\0';
    printf("%s",buf);
}

