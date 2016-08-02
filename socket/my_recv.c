/*************************************************************************
	> File Name: my_recv.c
	> Author:motian 
	> Mail:765885195@qq.com 
	> Created Time: 2016年08月02日 星期二 09时36分56秒
 ************************************************************************/

#define MY_RECV_C

#include<stdio.h>
#include<string.h>
#include<error.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<stdlib.h>
#include"my_recv.h"


//自定义的错误处理函数
void my_error(const char *err_string, int line)
{
    fprintf(stderr,"ine:%d ",line);
    perror(err_string);
    exit(1);
}

//自定义的my_recv

int my_recv(int conn_fd, char *data_buf,int len)
{
    static char recv_buf[BUFSIZE];
    static char *pread;
    static int  len_remain = 0;
    int         i;

    //如果自定义的缓冲区中没有数据，则从套接字中读取数据
    if((len_remain = recv(conn_fd, recv_buf, sizeof(recv_buf),0)) < 0)
    {
        my_error("recv",__LINE__);
    }
    else if(len_remain==0)  //目的计算机的socket关闭
    {
        return 0;
    }
    pread = recv_buf;  //重新初始化pread指针

    //从自定义缓冲区中读取一次数据
    for(i=0;*pread!='\n';i++)
    {
        if(i > len)
        {
            return -1;
        }
        data_buf[i] = *pread++;
        len_remain--;
    }

    //去除结束标志
    len_remain--;
    pread++;

    return i; //读取成功
}
