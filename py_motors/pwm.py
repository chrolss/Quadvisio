import Adafruit_BBIO.PWM as PWM
import time

def initialize():
	PWM.start("P8_13",20,200)
	time.sleep(0.5)
	print('P8_13 initialized')
	PWM.start("P9_14",20,200)
	time.sleep(0.5)
	print('P9_14 initialized')
	time.sleep(1)

def set_pwm(a,b):
	PWM.set_duty_cycle("P8_13",a)
	PWM.set_duty_cycle("P9_14",b)

def close_pwm():
	PWM.set_duty_cycle("P8_13",20)
	PWM.set_duty_cycle("P9_14",20)
	time.sleep(1)
	PWM.stop("P8_13")
	PWM.stop("P9_14")
	PWM.cleanup()
	exit()
