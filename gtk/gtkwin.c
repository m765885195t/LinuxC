/*************************************************************************
	> File Name: gtkwin.c
	> Author:motian 
	> Mail:765885195@qq.com 
	> Created Time: 2016年07月30日 星期六 15时20分55秒
 ************************************************************************/


#include<gtk/gtk.h>

void hello(GtkWidget *widget,gpointer *data)
{
    g_print("button clicked and data = %s\n",(char *)data );
}

void destroy(GtkWidget *widget, gpointer *data)
{
    gtk_main_quit();
}

int main(int argc,char *argv[])
{
    GtkWidget *window;
    GtkWidget *button;

    gtk_init (&argc,&argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(GTK_OBJECT(window),"destory",GTK_SIGNAL_FUNC(destroy),NULL);

    gtk_container_border_width(GTK_CONTAINER(window),20);

    button = gtk_button_new_with_label("Hello World");
    g_signal_connect(GTK_OBJECT(button),"clicked",GTK_SIGNAL_FUNC(hello),"I am from button");

    gtk_container_add(GTK_CONTAINER(window),button);

    gtk_widget_show(button);
    gtk_widget_show(window);

    gtk_main();

    return 0;
}
