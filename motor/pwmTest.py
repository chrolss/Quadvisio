#!/usr/bin/python

import Adafruit_BBIO.PWM as PWM
import time

PWM.start("P8_13",4,50)

while True:
	i = input("Enter a number")
	if i < 100:
		PWM.set_duty_cycle("P8_13",float(i))
		print "duty set to: ",i,""
	else:	
		break

PWM.stop("P8_13")
PWM.cleanup()
quit()
