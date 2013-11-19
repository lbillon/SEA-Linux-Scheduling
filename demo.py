#!/usr/bin/python

import subprocess
import os
from time import sleep

def wk():
	raw_input("-")

def test2():
	print "Test 2 : Slowly increasing Timidity niceness to 19"
	for i in range(0,5):
	        with open(os.devnull, 'w') as devnull:
	                subprocess.call('renice -n %s %s'%(i,timidity_process.pid), shell=True,stdout=devnull)
	        print "Timidity Priority is now %s"%i
		wk()
	
	print "Setting back Timidity niceness to 0"
	print "Sound should work nicely"
	with open(os.devnull, 'w') as devnull:
	        subprocess.call('renice -n 0 %s'%timidity_process.pid, shell=True,stdout=devnull)
	wk()

	print "Slowly decreasing Blink niceness to -5"
	for i in range(0,-5,-1):
	        with open(os.devnull, 'w') as devnull:
	                subprocess.call('renice -n %s %s'%(i,blink_process.pid), shell=True,stdout=devnull)
	        print "Priority is now %s"%i
	        wk()
	print "Sound should be awful"
	wk()
	print "Setting blink niceness to -20"
	with open(os.devnull, 'w') as devnull:
	        subprocess.call('renice -n %s %s'%(-20,blink_process.pid), shell=True,stdout=devnull)
	print "LED should blink super fast"
	wk()

print "Starting processes"
with open(os.devnull, 'w') as devnull:
	timidity_process = subprocess.Popen(['timidity', '/home/pi/jbg.mid'],stdout=devnull)
	blink_process = subprocess.Popen(['./blink.py'],stdout=devnull)
print "Timidity has pid %s"%timidity_process.pid
print "Blink process has pid %s"%blink_process.pid

print "Sound should work nicely"

wk()

#test2()

print "Changing scheduling policy for Timidity to SCHED_RR with priority 10"
with open(os.devnull, 'w') as devnull:
	subprocess.call('renice -n %s %s'%(0,blink_process.pid), shell=True,stdout=devnull)
        subprocess.call('sudo chrt -r -p %s %s'%(10,timidity_process.pid), shell=True,stdout=devnull)
wk()

print "Changing scheduling policy for BLinker to SCHED_RR with priority 10"
with open(os.devnull, 'w') as devnull:
        subprocess.call('sudo chrt -r -p %s %s'%(10,blink_process.pid), shell=True,stdout=devnull)
wk()

print "Change blink process priority to 11"
with open(os.devnull, 'w') as devnull:
        subprocess.call('sudo chrt -r -p %s %s'%(11,blink_process.pid), shell=True,stdout=devnull)


print "Changing scheduling policy for Timidity and Blinker to SCHED_FIFO with priority 10"
with open(os.devnull, 'w') as devnull:
        subprocess.call('sudo chrt -f -p %s %s'%(10,timidity_process.pid), shell=True,stdout=devnull)
        subprocess.call('sudo chrt -f -p %s %s'%(10,blink_process.pid), shell=True,stdout=devnull)
wk()

print "Change blink process priority to 11"
with open(os.devnull, 'w') as devnull:
        subprocess.call('sudo chrt -f -p %s %s'%(11,blink_process.pid), shell=True,stdout=devnull)
print "end"
sleep(10000)
