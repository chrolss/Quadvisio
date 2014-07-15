import Adafruit_BBIO.PWM as PWM
import time

PWM.start("P8_13",49,200)
print('Set to max')
time.sleep(1)
print('insert battery, calibration starts in 5 seconds')
time.sleep(5)
print('setting to zero')
PWM.set_duty_cycle("P8_13",20)
print('set to zero')
time.sleep(1)
PWM.stop("P8_13")
PWM.cleanup()
print('exit program')
exit()