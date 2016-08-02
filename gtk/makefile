cc=gcc

program=gtkwin

#PATH += /usr/include/gtk2.0
LDLIBS=`pkg-config --libs gtk+-2.0`

CFLAGS= -Wall -g `pkg-config --cflags gtk+-2.0`

$(program):$(program).c
$(cc) $(LDLIBS) $(program).o -o $(program)


$(program).o:$(program).c
$(cc) $(CFLAGS) -c $(program).c

clean:
	-rm -f *.o
