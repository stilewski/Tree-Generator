# makefile...

APPNAME=test
CC=g++
CFLAGS=-c -Wall

GTK_INC=
GTK_LIB=-lgtkglext-x11-1.0 -lgdkglext-x11-1.0 -lglib-2.0 -lgtk-x11-2.0 -lX11 -lgdk-x11-2.0 -lgdk_pixbuf-2.0 -lm -lgobject-2.0

GL_INC=
GL_LIB=-lGL -lGLU

INC=-I/usr/include/gtk-2.0 -I/usr/lib/gtk-2.0/include -I/usr/include/atk-1.0 -I/usr/include/cairo -I/usr/include/pango-1.0 -I/usr/include/pixman-1 -I/usr/include/freetype2 -I/usr/include/directfb -I/usr/include/libpng12 -I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include -I/usr/include/gtkglext-1.0 -I/usr/lib/gtkglext-1.0/include

L_GTK_FLAGS=-lgtkglext-x11-1.0 -lgdkglext-x11-1.0
OBJS=main.o Vector3d.o CLeaf.o CRoot.o CBranch.o CPlant.o CRand.o LabelledWidget.o TextureMgr.o Scene.o

project : $(OBJS)
	$(CC) $(OBJS) -Wall $(INC) -o $(APPNAME) $(GTK_LIB) $(GL_LIB)


main.o : main.c LabelledWidget.o TextureMgr.o Scene.o CPlant.o
	$(CC) $(INC) $(CFLAGS) main.c

Vector3d.o : Vector3d.c Vector3d.h
	$(CC) $(CFLAGS) Vector3d.c

CLeaf.o : CLeaf.c CLeaf.h Vector3d.h Vector3d.c Scene.h Scene.c
	$(CC) $(CFLAGS) CLeaf.c

CRoot.o : CRoot.c CRoot.h Vector3d.h Vector3d.c Scene.h Scene.c
	$(CC) $(CFLAGS) CRoot.c

CBranch.o : CBranch.c CBranch.h Vector3d.h Vector3d.c CRoot.c CRoot.h CLeaf.h CLeaf.c
	$(CC) $(CFLAGS) CBranch.c

CPlant.o : CPlant.c CPlant.h Vector3d.o CBranch.c CBranch.h CLeaf.c CLeaf.h CRoot.h CRoot.c CRand.c CRand.o
	$(CC) $(CFLAGS) CPlant.c

CRand.o : CRand.c CRand.h
	$(CC) $(CFLAGS) CRand.c

LabelledWidget.o : LabelledWidget.c LabelledWidget.h
	$(CC) $(INC) -c -Wall LabelledWidget.c

TextureMgr.o : TextureMgr.c TextureMgr.h
	$(CC) $(CFLAGS) TextureMgr.c


clean : $(OBJS)
	rm $(OBJS)
