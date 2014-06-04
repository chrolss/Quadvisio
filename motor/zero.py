import Adafruit_BBIO.PWM as PWM

PWM.start("P8_13",4,50)

PWM.stop("P8_13")
PWM.cleanup()
