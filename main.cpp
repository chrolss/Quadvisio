#include <iostream>
#include <Sensors/adxl345.h>
#include <motor/motorPWM.h>


int main(int argc, char** argv) {
	adxl345 adxl;
	motorPWM PWM(argc, argv);
	for (int j=0; j<5000; j++)
	{
		adxl.readSensorData();
		short x = adxl.getAccX();
		if (x>0)
		{
			if(x<180)
			{
				PWM.setPWM("7");
				std::cout << "7" << std::endl;
			}
			else
			{
				PWM.setPWM("9");
				std::cout << "9" << std::endl;
			}
		}
		else
		{
			if(x<-180)
			{
				PWM.setPWM("4");
				std::cout << "4" << std::endl;
			}
			else
			{
				PWM.setPWM("5");
				std::cout << "5" << std::endl;
			}
		}
	}
    // Testa de klasser som man vill testa
    
    return 0;
}
