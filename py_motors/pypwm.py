import Adafruit_BBIO.PWM as PWM
import time


def initialize(a,b,c,d):
	print("inne i initialize")
	PWM.start("P8_13",0,200)
	time.sleep(0.5)
	print('P8_13 initialized')
	PWM.start("P9_14",0,200)
	time.sleep(0.5)
	print('P9_14 initialized')
	PWM.start("P9_21",0,200)
	time.sleep(0.5)
	print('P9_21 initialized')
	time.sleep(0.5)
	PWM.start("P9_42",0,200)
	print('P9_42 initialized')
	time.sleep(0.5)
	PWM.set_duty_cycle("P9_42",20)
	PWM.set_duty_cycle("P8_13",20)
	PWM.set_duty_cycle("P9_14",20)
	PWM.set_duty_cycle("P9_21",20)
	time.sleep(0.5)
	PWM.set_duty_cycle("P9_42",23)
	PWM.set_duty_cycle("P8_13",b)
	PWM.set_duty_cycle("P9_14",c)
	PWM.set_duty_cycle("P9_21",d)
	

def set_pwm(a,b,c,d):
	PWM.set_duty_cycle("P8_13",float(a))
	print a
	PWM.set_duty_cycle("P9_16",float(b))
	print b
	PWM.set_duty_cycle("P9_21",float(c))
	print c
	PWM.set_duty_cycle("P9_42",float(d))
	print d
	

def close_pwm(a,b,c,d):
	print("inne i close")
	PWM.set_duty_cycle("P8_13",20)
	PWM.set_duty_cycle("P9_14",20)
	PWM.set_duty_cycle("P9_21",20)
	PWM.set_duty_cycle("P9_42",20)
	time.sleep(1)
	PWM.set_duty_cycle("P8_13",0)
	PWM.set_duty_cycle("P9_14",0)
	PWM.set_duty_cycle("P9_21",0)
	PWM.set_duty_cycle("P9_42",0)
	exit()
