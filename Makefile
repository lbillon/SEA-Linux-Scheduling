all:
	gcc switch_sched_example.c -o switch_sched_example.bin
	gcc work.c -o work.bin
	gcc blink.c -lwiringPi -o blink.bin
