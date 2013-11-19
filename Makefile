CC = gcc
CFLAGS  = -g -Wall

all:
	$(CC) $(CFLAGS) switch_sched_example.c -o switch_sched_example.bin -pthread
	$(CC) $(CFLAGS) work.c -o work.bin
	$(CC) $(CFLAGS) blink.c -lwiringPi -o blink.bin
