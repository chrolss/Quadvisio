#include <iostream>
#include <stdio.h>
#include "kalman.h"

double input;
double est;

int main(){
	kalman filter(0.01, 0.01, 10, 10);
	for (int i = 0; i<10; i++){
		std::cin >> input;
		est = filter.estimate(input);
		printf("measurment was %f, and estimated state is: %f \n", input, est);
	}
}
