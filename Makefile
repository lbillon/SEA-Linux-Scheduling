all:
	gcc switch_sched_example.c -o switch_sched_example.bin -pthread
	gcc work.c -o work.bin
