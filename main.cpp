#include <iostream>
#include <Sensors/adxl345.h>
#include <motor/motorPWM.h>


int main(int argc, char** argv) {
	adxl345 adxl;
	motorPWM PWM(argc, argv);
	PWM.setPWM("4");
	for (int j=0; j<5000; j++)
	{
		adxl.readSensorData();
		short x = adxl.getAccX();
		if (x>0)
		{
			if(x<180)
			{
				PWM.setPWM("5.53");
				std::cout << "5.53" << std::endl;
			}
			else
			{
				PWM.setPWM("5.54");
				std::cout << "5.54" << std::endl;
			}
		}
		else
		{
			if(x<-180)
			{
				PWM.setPWM("5.51");
				std::cout << "5.51" << std::endl;
			}
			else
			{
				PWM.setPWM("5.52");
				std::cout << "5.52" << std::endl;
			}
		}
	}
    // Testa de klasser som man vill testa
    
    return 0;
}
