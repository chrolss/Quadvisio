import Adafruit_BBIO.PWM as PWM


def init():
	PWM.start("P8_13",4,50)

def close():
	PWM.stop("P8_13")
	PWM.cleanup()
	quit()

def setPWM(a):
	print float(a)
    i = input("Set duty cycle from python: ")
	PWM.set_duty_cycle("P8_13",float(i))

