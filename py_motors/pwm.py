import Adafruit_BBIO.PWM as PWM
import time


def initialize():
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

def set_pwm1(a):
	PWM.set_duty_cycle("P8_13",a)

def set_pwm1(a):
	PWM.set_duty_cycle("P9_14",a)
	
def set_pwm1(a):
	PWM.set_duty_cycle("P9_21",a)

def set_pwm1(a):
	PWM.set_duty_cycle("P9_42",a)
		
def set_pwm(a,b,c,d):
	print("inne i set_pwm")
	e = "hej"
	PWM.set_duty_cycle("P8_13",25)
	print e
	PWM.set_duty_cycle("P9_16",25)
	print e
	PWM.set_duty_cycle("P9_21",25)
	print e
	PWM.set_duty_cycle("P9_42",25)
	print e
	

def close_pwm():
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
	print("slut pa close")
