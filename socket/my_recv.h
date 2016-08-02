/*************************************************************************
	> File Name: my_recv.h
	> Author:motian 
	> Mail:765885195@qq.com 
	> Created Time: 2016年08月02日 星期二 09时53分36秒
 ************************************************************************/

#ifndef _MY_RECV_H
#define _MY_RECV_H
    #define BUFSIZE 1024
    void my_err(const char *err_string, int line);
    int my_recv(int conn_fd, char  *data_buf, int line);
#endif
