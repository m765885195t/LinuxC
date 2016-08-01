gtkwin:gtkwin.o
	gcc gtkwin.o -o gtkwin.c `pkg-config --libs --cflags gtk+-2.0`
gtkwin.o:gtkwin.c gtk/gtk.h
	gcc -c gtkwin.c `pkg-config --libs --cfags gtk+-2.0`
clean:
	rm -rf *.o gtkwin.o
#怎么编写
