import Adafruit_BBIO.PWM as PWM
import time

def initialize():
	PWM.start("P8_13",20,200)
	time.sleep(0.5)
	print('P8_13 initialized')
	PWM.start("P9_14",20,200)
	time.sleep(0.5)
	print('P9_14 initialized')
	PWM.start("P9_21",20,200)
	time.sleep(0.5)
	print('P8_19 initialized')
	PWM.start("P9_42",20,200)
	time.sleep(0.5)
	print('P9_42 initialized')
	time.sleep(2)

def set_pwm1(a):
	PWM.set_duty_cycle("P8_13",a)
	
def set_pwm2(a):
	PWM.set_duty_cycle("P9_14",a)
	
def set_pwm3(a):
	PWM.set_duty_cycle("P9_21",a)

def set_pwm4(a):
	PWM.set_duty_cycle("P9_42",a)

def set_pwm(a):
	PWM.set_duty_cycle("P8_13",a)
	PWM.set_duty_cycle("P9_14",a)


def close_pwm():
	PWM.set_duty_cycle("P8_13",20)
	PWM.set_duty_cycle("P9_14",20)
	PWM.set_duty_cycle("P9_21",20)
	PWM.set_duty_cycle("P9_42",20)
	time.sleep(1)
	PWM.stop("P8_13")
	PWM.stop("P9_14")
	PWM.stop("P9_21")
	PWM.stop("P9_42")
	PWM.cleanup()
	exit()
