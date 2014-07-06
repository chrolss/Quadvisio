import Adafruit_BBIO.PWM as PWM
import time


PWM.start("P8_13",20,200)
time.sleep(0.5)
PWM.start("P8_19",20,200)

foo = input('Enter a PWM value, 20 - 49: ')
PWM.setDutyCycle("P8_13",foo)
time.sleep(2)
PWM.setDutyCycle("P8_13",20)
foos = input('Enter a PWM value, 20 -49: ')
PWM.setDutyCycle("P8_19", foos)
time.sleep(2)
PWM.setDutyCycle("P8_19",20)

print('PWM program shutting down')
PWM.stop("P8_13")
PWM.stop("P8_19")
exit()

