import Adafruit_BBIO.PWM as PWM
import time

def initialize():
	PWM.start("P8_13",20,200)
	print('P8_13 initialized')

def set_pwm(a):
	PWM.set_duty_cycle("P8_13",a)

def close_pwm():
	PWM.set_duty_cycle("P8_13",20)
	time.sleep(0.1)
	PWM.stop("P8_13")
