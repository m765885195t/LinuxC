/*********************************************************************************
  * 文件名称：get_cmd.c
  * 功能描述：提供键值实现，backspace/enter/上翻、下翻
  * 维护记录：2009-3-25     V1.01    by skyily
 *********************************************************************************/
#include "main.h"
#include "keypress.h"

/*********************************************************************************
 * 语法格式： char *get_cmd(char *buf)
 * 实现功能： 把键盘上获取的命令储存到buf
 * 入口参数： char *buf
 * 出口参数： char *buf
 *********************************************************************************/
char *get_cmd(char *buf)
{
    int len = 0;
    int i = 0;
    char tmp_buf[CMD_SIZE] = {""};
    char ch;
    TYPE *p = head;

    set_keypress();
    
    while(1)
    {
        ch = getchar();
        if(ch == 27)
        {
            getchar();
            if((ch = getchar()) == 65 || ch == 66)
            {
                if(ch == 65)        //key up and get his_cmd
                {
                    len = strlen(tmp_buf);
                    memset(tmp_buf, 0, CMD_SIZE);
                    
                    strcpy(tmp_buf, p->his_cmd);        //up
                    tmp_buf[strlen(tmp_buf) - 1] = '\0';
                    
                    if(p->next_b != head)                //stop
                    {
                        p = p->next_b;
                    }
                    printf("\r[%s@localhost %s]$ ", getlogin(), my_dir_cu);
                    for(i = 0; i < len; i++)            //AAAAAAAAAAA
                    {
                        printf(" ");        //erasure line memory
                    }
                    
                    printf("\r[%s@localhost %s]$ %s", getlogin(), my_dir_cu, tmp_buf);
                    fflush(stdout);
                }
                else if(ch == 66)    //key down and get his_cmd
                {
                    len = strlen(tmp_buf);
                    memset(tmp_buf, 0, CMD_SIZE);
                
                    if(p == head)
                    {
                        printf("\a");
                    }
                    //if(p != head)                //stop
                    else
                    {
                        p = p->next_f;
                        strcpy(tmp_buf, p->his_cmd);        //down
                        tmp_buf[strlen(tmp_buf) - 1] = '\0';
                    }

                    printf("\r[%s@localhost %s]$ ", getlogin(), my_dir_cu);
                    for(i = 0; i < len; i++)
                    {
                        printf(" ");        //erasure line memory
                    }
                    
                    printf("\r[%s@localhost %s]$ %s", getlogin(), my_dir_cu, tmp_buf);
                    fflush(stdout);
                }
            }
        }
        else if(ch == 127)            //key backspace
        {
            len = strlen(tmp_buf);
            if(len == 0)
            {
                printf("\a");
            }
            //if(len != 0)
            else
            {
                tmp_buf[len - 1] = '\0';        //erasure single character
                len--;
                printf("\r[%s@localhost %s]$ ", getlogin(), my_dir_cu);
                for(i = 0; i < (len + 1); i++)
                {
                    printf(" ");            //erasure line memory
                }
                printf("\r[%s@localhost %s]$ %s", getlogin(), my_dir_cu, tmp_buf);
                fflush(stdout);
            }
        }
        else if(ch == 10)
        {
            strcat(tmp_buf, "\n");            //
            strcpy(buf, tmp_buf);            //get cmd_buf
            printf("\n");                    //necessary importantAAAAAAAAAA
            reset_keypress();                //
            break;
        }
        else
        {
            len = strlen(tmp_buf);
            printf("%c", ch);
            tmp_buf[len] = ch;
            len++;
        }            
    }
    return buf;
}

//keypress.h


/*********************************************************************************
  * 文件名称：keypress.h
  * 功能描述：提供uart模式功能
  * 维护记录：2009-3-25     V1.01    by skyily
 *********************************************************************************/

#ifndef _INCLUDE_KEYPRESS_H_
#define _INCLUDE_KEYPRESS_H_

#include <termios.h>

void set_keypress(void);
void reset_keypress(void);

#endif //_INCLUDE_KEYPRESS_H_

//keypress.c

#include "keypress.h"
#include <termios.h>
/*********************************************************************************
 * 语法格式： void set_keypress(void)
 * 实现功能： 实现uart模式
 * 入口参数： 无
 * 出口参数： 无
 *********************************************************************************/
static struct termios old_settings;

void set_keypress(void)
{
    struct termios new_settings;
    tcgetattr(0, &old_settings);
    new_settings = old_settings;

    /* Disable canonical mode, and set buffer size to 1 byte */
    new_settings.c_lflag &= (~ICANON);
    new_settings.c_lflag &= (~ECHO);
    
    new_settings.c_cc[VTIME] = 0;
    new_settings.c_cc[VMIN] = 1;

    tcsetattr(0, TCSANOW, &new_settings);
    return;
}

void reset_keypress(void)
{
    tcsetattr(0, TCSANOW, &old_settings);
    return;
}
