import Adafruit_BBIO.PWM as PWM
import time

PWM.start("P8_13",20,200)
time.sleep(0.5)
PWM.start("P9_14",20,200)
time.sleep(0.5)
PWM.start("P9_21",20,200)
time.sleep(0.5)
PWM.start("P9_42",20,200)

a = 20
b = 20
c = 20
d = 20

while True:
	print("Choose motor")
	print("1 = P8_13",  a)
	print("2 = P9_14",  b)
	print("3 = P9_21",  c)
	print("4 = P9_42",  d)
	print("5 = Alla")
	i = input("ange motor: ")
	if i == 1:
		k = input("Ange change for P8_13: ")
		a = a + k
		print(a)
		PWM.set_duty_cycle("P8_13",a)
	elif i == 2:
		k = input("Ange change for P9_14: ")
		b = b + k
		print(b)
		PWM.set_duty_cycle("P9_14",b)
	elif i == 3:
		k = input("Ange change for P9_21: ")
		c = c + k
		print(c)
		PWM.set_duty_cycle("P9_21",c)
	elif i == 4:
		k = input("Ange change for P9_42: ")
		d = d + k
		print(d)
		PWM.set_duty_cycle("P9_42",d)
	elif i == 5:
		k = input("Ange change for alla: ")
		a = a + k
		b = b + k
		c = c + k
		d = d + k
		PWM.set_duty_cycle("P8_13",a)
		PWM.set_duty_cycle("P9_14",b)
		PWM.set_duty_cycle("P9_21",c)
		PWM.set_duty_cycle("P9_42",d)
	else:
		PWM.set_duty_cycle("P8_13",20)
		PWM.set_duty_cycle("P9_14",20)
		PWM.set_duty_cycle("P9_21",20)
		PWM.set_duty_cycle("P9_42",20)
		time.sleep(0.5)
		break
		
print("slut")
	