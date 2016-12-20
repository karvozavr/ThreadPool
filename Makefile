CC      = gcc
CFLAGS  = -g -Wall -Wextra -Wshadow -Werror -ansi -pedantic -std=c99
LDFLAGS = -lpthread

all: thread_pool

thread_pool: main.o computation.o thread_pool.o linkedlist.o queue.o squeue.o wsqueue.o
	$(CC) $(CFLAGS) main.o computation.o thread_pool.o linkedlist.o queue.o squeue.o wsqueue.o $(LDFLAGS) -o thread_pool

main.o: main.c
	$(CC) -c main.c $(CFLAGS) -o main.o

computation.o: computation.c
	$(CC) -c computation.c $(CFLAGS) -o computation.o

thread_pool.o: thread_pool.c
	$(CC) $(CFLAGS) -c thread_pool.c -o thread_pool.o

linkedlist.o: linkedlist.c
	$(CC) $(CFLAGS) -c linkedlist.c -o linkedlist.o

queue.o: queue.c
	$(CC) $(CFLAGS) -c queue.c -o queue.o

squeue.o: squeue.c
	$(CC) $(CFLAGS) -c squeue.c -o squeue.o

wsqueue.o: wsqueue.c
	$(CC) $(CFLAGS) -c wsqueue.c -o wsqueue.o



.PHONY: clean

clean:
	rm *.o thread_pool
