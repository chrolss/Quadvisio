import Adafruit_BBIO.PWM as PWM
import time


PWM.start("P8_13",20,200)
time.sleep(0.5)
print('P8_13 initialized')
PWM.start("P9_14",20,200)
time.sleep(0.5)
print('P9_14 initialized')

foo = input('Enter a PWM value, 20 - 49: ')
fos = input('Enter a PWM value, 20 - 49: ')
PWM.set_duty_cycle("P8_13",foo)
PWM.set_duty_cycle("P9_14",fos)
time.sleep(2)
PWM.set_duty_cycle("P8_13",20)
PWM.set_duty_cycle("P9_14",20)
time.sleep(1)
print('PWM program shutting down')
PWM.stop("P8_13")
PWM.stop("P9_14")
PWM.cleanup()
exit()

