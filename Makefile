# Makefile for executable Quick14

# *****************************************************
# Parameters to control Makefile operation

CC = gcc
CFLAGS = -c99 -pedantic -Wall -g

# ****************************************************
# Entries to bring the executable up to date

Quick14: Quick14.o stack.o getLine.o
	$(CC) $(CFLAGS) -o Quick14 Quick14.o stack.o getLine.o

Quick14.o: Quick14.c stack.h getLine.h
	$(CC) $(CFLAGS) -c Quick14.c

stack.o: stack.c stack.h
	$(CC) $(CFLAGS) -c stack.c
    
getLine.o: getLine.c getLine.h
	$(CC) $(CFLAGS) -c getLine.c