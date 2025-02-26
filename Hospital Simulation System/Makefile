CC=g++
CFLAGS=-g -ansi -Wall -pedantic-errors -O0

all: main

main: Actors.h FCFSList.h FCFSList_impl.h SortedList.h SortedList_impl.h Hospital.h Hospital.cpp main.cpp
	$(CC) $(CFLAGS) main.cpp Hospital.cpp -o main.out

clean:
	rm main.out