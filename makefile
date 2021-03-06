CC=g++
CFLAGS=-g -Wall -O3 -fast
IFLAGS=-I/usr/X11R6/include
LFLAGS=-L/usr/X11R6/lib -lX11
all: turtle

turtle: turtle.cc points.cc graphics.cc matrix.cc draw.cc turtle_class.cc input_output.cc elementary_program.cc recursive_program.cc interface.cc 
	$(CC) $(CFLAGS) $(IFLAGS) -o turtle turtle.cc $(LFLAGS) -lm

clean: rm turtle
