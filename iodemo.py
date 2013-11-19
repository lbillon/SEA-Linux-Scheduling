#!/usr/bin/python

import subprocess
import os
from time import sleep

print "Starting processes"
with open(os.devnull, 'w') as devnull:
	timidity_process = subprocess.Popen(['timidity', '/home/pi/jbg.mid'],stdout=devnull)
print "Timidity has pid %s"%timidity_process.pid
print "Setting Timidity priority to 19"
with open(os.devnull, 'w') as devnull:
        subprocess.call('renice -n 19 %s'%timidity_process.pid, shell=True,stdout=devnull)
sleep(5)
print "Running writer process with priority -15"
with open(os.devnull, 'w') as devnull:
	writer_process = subprocess.Popen(['./writer.py'],stdout=devnull)
        subprocess.call('renice -n -15 %s'%writer_process.pid, shell=True,stdout=devnull)
writer_process.wait()

print "Writer has finished, killing sound"
timidity_process.kill()

try:
    os.remove('writer.log')
except OSError:
    pass

print "Run writer alone"
with open(os.devnull, 'w') as devnull:
	writer_process = subprocess.Popen(['./writer.py'],stdout=devnull)
writer_process.wait()

print "Run writer with worker" 
with open(os.devnull, 'w') as devnull:
	worker_process = subprocess.Popen(['./blink.py'],stdout=devnull)
	sleep(1)
	writer_process = subprocess.Popen(['./writer.py'],stdout=devnull)
writer_process.wait()
worker_process.kill()
print "All tests have finished, please see results in writer.log"
