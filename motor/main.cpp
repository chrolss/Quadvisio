//
//  main.cpp
//  Atlas Software
//
//  Created by Quadvisio on 2014-06-06 as part of the Atlas Project.
//  Copyright (c) 2014 Quadvisio. All rights reserved.
//

#include <iostream>
#include <string>
#include "Motor.h"

int main(int argc, const char * argv[])
{
	float tal;
	Motor pwm1(1);
	Motor pwm2(2);
	Motor pwm3(3);
	Motor pwm4(4);
	while (true){
		printf("Ge pwm-värde\n");
		std::cin >> tal;
		if (tal > 100){
			pwm1.closePWM();
			pwm2.closePWM();
			pwm3.closePWM();
			pwm4.closePWM();
			exit(1);
		}
		pwm1.setPWM(tal);
		pwm2.setPWM(tal);
		pwm3.setPWM(tal);
		pwm4.setPWM(tal);

	}


    return 0;
}

