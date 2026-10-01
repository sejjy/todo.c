CC = gcc
CFLAGS = -O -Wall -W -pedantic -ansi -std=c99

todo: todo.o readline.o
	$(CC) $(CFLAGS) -o todo todo.o readline.o

todo.o: todo.c readline.h
	$(CC) $(CFLAGS) -c todo.c

readline.o: readline.c readline.h
	$(CC) $(CFLAGS) -c readline.c
