#!/usr/bin/python

import RPi.GPIO as GPIO
from time import sleep

GPIO.setmode(GPIO.BCM)
GPIO.setup(16, GPIO.OUT)
while True :
	GPIO.output(16, GPIO.LOW)
	for i in range(1,1000000):
		pass
	GPIO.output(16, GPIO.HIGH)
