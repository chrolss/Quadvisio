#include "Controller.h"
#include <iostream>

double params[9];
double refs[3];


int main(){
	controller = new Controller;
	controller->setParameters(params);
	controller->setReference(refs);
}
