CC = gcc
CFLAGS  = -g -Wall

default : all
all: sched
	$(CC) $(CFLAGS) work.c -o work.bin
	$(CC) $(CFLAGS) blink.c -lwiringPi -o blink.bin

sched : switch_sched_example.c
	$(CC) $(CFLAGS) switch_sched_example.c -o switch_sched_example.bin -pthread
