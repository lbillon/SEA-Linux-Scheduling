#!/usr/bin/python

import subprocess
import os
from time import sleep
def test2():
	print "Test 2 : Slowly increasing Timidity niceness to 19"
	for i in range(0,5):
	        with open(os.devnull, 'w') as devnull:
	                subprocess.call('renice -n %s %s'%(i,timidity_process.pid), shell=True,stdout=devnull)
	        print "Timidity Priority is now %s"%i
	        sleep(3)
	sleep(5)
	print "Setting back Timidity priority to 0"
	print "Sound should work nicely"
	with open(os.devnull, 'w') as devnull:
	        subprocess.call('renice -n 0 %s'%timidity_process.pid, shell=True,stdout=devnull)
	sleep(5)

	print "Slowly decreasing Blink niceness to -5"
	for i in range(0,-5,-1):
	        with open(os.devnull, 'w') as devnull:
	                subprocess.call('renice -n %s %s'%(i,blink_process.pid), shell=True,stdout=devnull)
	        print "Priority is now %s"%i
	        sleep(3)
	print "Sound should be awful"
	sleep(5)
	print "Setting blink niceness to -20"
	with open(os.devnull, 'w') as devnull:
	        subprocess.call('renice -n %s %s'%(-20,blink_process.pid), shell=True,stdout=devnull)
	print "LED should blink super fast"
	sleep(5)

print "Starting processes"
with open(os.devnull, 'w') as devnull:
	timidity_process = subprocess.Popen(['timidity', '/home/pi/jbg.mid'],stdout=devnull)
	blink_process = subprocess.Popen(['./blink.py'],stdout=devnull)
print "Timidity has pid %s"%timidity_process.pid
print "Blink process has pid %s"%blink_process.pid

sleep(10)
print "Sound should work nicely"

test2()

print "Changing scheduling policy for Timidity to SCHED_RR"
with open(os.devnull, 'w') as devnull:
        subprocess.call('sudo chrt -r -p %s %s'%(1,timidity_process.pid), shell=True,stdout=devnull)


sleep(10000)
