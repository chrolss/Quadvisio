#!/usr/bin/python

import Adafruit_BBIO.PWM as PWM
import time
import os
import sys
import __future__

def double(a):
	b = float(a)
	return a
	
def mupp(a,b):
	c = float(a) + float(b/100)
	PWM.start("P8_13",20,200)
	time.sleep(0.1)
	PWM.set_duty_cycle("P8_13",0)
	time.sleep(0.1)
	PWM.set_duty_cycle("P8_13",20)
	PWM.stop("P8_13")
	d = str(c)
	return d
	
def fupp(a):
	b = float(a)
	PWM.start("P8_13",20,200)
	time.sleep(1)
	PWM.set_duty_cycle("P8_13",b)
	time.sleep(2)
	PWM.set_duty_cycle("P8_13",20)
	PWM.stop("P8_13")
	return a