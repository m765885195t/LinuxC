/*************************************************************************
	> File Name: 7.c
	> Author: 
	> Mail: 
	> Created Time: 2016年08月08日 星期一 17时07分41秒
 ************************************************************************/

#include<stdio.h>
int main()
{
    char ch;
    char buf[123];
    int i;
    while(1)
    {
        if((ch = getche()) != '\n')
        {
            buf[i++] = ch;
            printf("\b \b*");
        }
        else
        {
            break;   
        }
    }
}
