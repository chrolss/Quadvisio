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
	float pwmTal[4];
	Motor pwm;
	while (true){
		printf("Ge pwm-värde\n");
		std::cin >> tal;
		if (tal > 100){
			pwm.closePWM();
			exit(1);
		}
		pwmTal[0] = tal;
		pwmTal[1] = tal;
		pwmTal[2] = tal;
		pwmTal[3] = tal;

		pwm.setPWM(pwmTal);
	}


    return 0;
}

