#!/usr/bin/python
import time
f = open('/tmp/writer','w')
text = ''
for i in range(0,1000):
	text=text+'hello'
startt=time.time()
for i in range(1,30000):
	f.write(text)
f.close()
endt=time.time()

logf = open('writer.log','a')
logf.write('Start time : %s, end time : %s, running time : %s\n'%(startt,endt,endt-startt))
