//
//  main.cpp
//  QuadLib
//
//  Created by Toni Axelsson on 2014-07-11.
//  Copyright (c) 2014 Quadvisio. All rights reserved.
//

#include <iostream>
#include <string>
#include <unistd.h>

#include "QuadPWM.h"
#include "QuadGPIO.h"
#include "QuadAIN.h"
#include "QuadGPS.h"

#define MOTOR_FL "P8_13"
#define MOTOR_FR "P9_14"
#define MOTOR_BL "P9_21"
#define MOTOR_BR "P9_42"

std::string tmp;


int main(int argc, const char * argv[]){
	QuadGPS GPS;
	printf("UART2 initialized?\n");
	while (true){
		printf("Press any key for read\n");
		std::cin >> tmp;
		GPS.readGPSData();
	}
}
/*
int main(int argc, const char * argv[]){
	QuadAIN AIN;	//initialize all AIN ports, 0 - 7
	printf("Analog ports initialized\n");
	int temp;
	int max;
	while (true){
			AIN.readAnalog(0);
			temp = AIN.getValue();
			if (temp > max){
				max = temp;
			}
			printf("Current %d \t Max: %d \n", temp, max);
			sleep(1);

	}
	return 0;
}
*/

/*
int main(int argc, const char * argv[]){
	QuadGPIO GPIO(68);
	printf("GPIO 68 initialized\n");
	GPIO.setDirection(0);
	sleep(1);
	for (int i = 0; i < 20; i++){
		GPIO.setValue(1);
		usleep(100000);
		GPIO.setValue(0);
		usleep(100000);
	}

	printf("Test avslutat\n");
	GPIO.release();
}
*/
/*
int main(int argc, const char * argv[]) {
    std::string s = "";
    
    int pwmInput = 0;
    
    QuadPWM pwm;
    pwm.initialize("P8_13");
    pwm.initialize("P9_14");
    pwm.initialize("P9_21");
    pwm.initialize("P9_42");
    
    sleep(1);
    
    while (true) {
        std::cout << "Enter pwm value" << std::endl;
        std::cin >> pwmInput;
        if (pwmInput<0) {
            break;
        }
        pwmInput = pwmInput*10000;
        
        pwm.setDuty(MOTOR_FR, pwmInput);
        pwm.setDuty(MOTOR_FL, pwmInput);
        pwm.setDuty(MOTOR_BL, pwmInput);
        pwm.setDuty(MOTOR_BR, pwmInput);

    }
    /*
    std::cout << "Setting duty to 1200000" << std::endl;
    pwm.setDuty("P8_13", 1200000);
    pwm.setDuty("P9_14", 1200000);
    pwm.setDuty("P9_21", 1200000);
    pwm.setDuty("P9_42", 1200000);
    */
/*
    sleep(1);
    std::cout << "Setting duty to 1000000" << std::endl;
    pwm.setDuty("P8_13", 1000000);
    pwm.setDuty("P9_14", 1000000);
    pwm.setDuty("P9_21", 1000000);
    pwm.setDuty("P9_42", 1000000);

    return 0;
}
*/
