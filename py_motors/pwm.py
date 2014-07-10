import Adafruit_BBIO.PWM as PWM
import time
import __future__


def initialize():
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

def set_pwm1(a):
	PWM.set_duty_cycle("P8_13",b)
	
def set_pwm2(a):
	PWM.set_duty_cycle("P9_14",b)
	
def set_pwm3(a):
	PWM.set_duty_cycle("P9_21",b)

def set_pwm4(a):
	PWM.set_duty_cycle("P9_42",b)

def close_pwm():
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
