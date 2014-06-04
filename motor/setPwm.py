import Adafruit_BBIO.PWM as PWM
import time

PWM.start("P8_13",5,50)
time.sleep(5)

PWM.set_duty_cycle("P8_13",4)
PWM.stop("P8_13")
PWM.cleanup()
