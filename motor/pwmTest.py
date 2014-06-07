#!/usr/bin/python

import Adafruit_BBIO.PWM as PWM
import time

PWM.start("P8_13",4,50)
PWM.set_duty_cycle("P8_13",4)
while (True):
	PWM.set_duty_cycle("P8_13",float(4))
	print "duty set to: 5.54 "	


PWM.stop("P8_13")
PWM.cleanup()
quit()
