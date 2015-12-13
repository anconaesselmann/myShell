# Makefile for executable testing

# *****************************************************
# Parameters to control Makefile operation

CC = gcc
CFLAGS = -pedantic -Wall -g

# ****************************************************
# Entries to bring the executable up to date

myshell: myshell.o String.o Shell.o IOScreen.o IOFile.o
	$(CC) $(CFLAGS) -o myshell myshell.o String.o Shell.o IOScreen.o IOFile.o

myshell.o: myshell.c Shell.h
	$(CC) $(CFLAGS) -c myshell.c

Shell.o: Shell.c IOScreen.o IOFile.o
	$(CC) $(CFLAGS) -c Shell.h Shell.c IO.h

String.o: String.c
	$(CC) $(CFLAGS) -c String.c

IOScreen.o: IOScreen.c
	$(CC) $(CFLAGS) -c IOScreen.c IOScreen.h

IOFile.o: IOFile.c
	$(CC) $(CFLAGS) -c IOFile.c IOFile.h