//
//  Controller.cpp
//  Atlas Software
//
//  Created by Quadvisio on 2014-06-06 as part of the Atlas Project.
//  Copyright (c) 2014 Quadvisio. All rights reserved.
//

#include "Controller.h"

Controller::Controller(){
    
}

void Controller::calcPWM(double *input, double *output) {
    
    for (int i=3; i<6; i++) {
        std::cout << "Deg: " << input[i] << " ";
        input[i] = input[i]*M_PI/180;
        std::cout << "Rad: " << input[i] << " ";
    }
    std::cout << std::endl;
    
    //alphadelen
	ea[0] = refs[0] - input[3];  	// set new error
	this->ea[2] += ea[0]*dt;
	Ma = parameters[0]*ea[0] + parameters[1]*(ea[2]) + parameters[2]*(ea[0]-ea[1]);
	this->ea[1] = ea[0];		// set old error

	//betadelen
	eb[0] = refs[1] - input[4];  	// set new error
	this->eb[2] += eb[0]*dt;
	Mb = parameters[3]*eb[0] + parameters[4]*(eb[2]) + parameters[5]*(eb[0]-eb[1]);
	this->eb[1] = eb[0];		// set old error

	//gammadelen
	eg[0] = refs[2] - input[5];  	// set new error
	this->eg[2] += eg[0]*dt;
	Mg = parameters[6]*eg[0] + parameters[7]*(eg[2]) + parameters[8]*(eg[0]-eg[1]);
	this->eg[1] = eg[0];		// set old error


	printf("Ma = %f, Mb = %f, Mg = %f, F = %f \n", Ma, Mb, Mg, F);
    
    Ma = Ma*COS45 - Mb*SIN45;
    Mb = Ma*SIN45 + Mb*COS45;

    output[0] = 0.25*(F*CONST1 + Mb*CONST2 + Mg*CONST3);
    output[1] = 0.25*(F*CONST1 - Ma*CONST2 - CONST3*Mg);
    output[2] = 0.25*(F*CONST1 - Mb*CONST2 + Mg*CONST3);
    output[3] = 0.25*(F*CONST1 + Ma*CONST2 - Mg*CONST3);
    
    printf("Before saturation \n");
    printf("LF = %f, RF = %f, RR = %f, RL = %f \n", output[0], output[1],output[2], output[3]);

    // Make sure output is between 0-100
    for (int i=0; i<4; i++) {
        if (output[i]<0) {
            output[i]=0.0;
        }
        output[i]=sqrt(output[i]);
        if (output[i]>100) {
            output[i]=100;
        }
    }
    printf("LF = %f, RF = %f, RR = %f, RL = %f \n", output[0], output[1],output[2], output[3]);

}

void Controller::setReference(double *ref){
	this->refs[0] = ref[0];
	this->refs[1] = ref[1];
	this->refs[2] = ref[2];
}

void Controller::setF(int _thrust){
	this->F = 4*THRUST_CONSTANT*_thrust*_thrust; 		//Toni fixar denna rad
}

void Controller::setParameters(double *params){
	this->parameters[0] = params[0];
	this->parameters[1] = params[1];
	this->parameters[2] = params[2];
	this->parameters[3] = params[3];
	this->parameters[4] = params[4];
	this->parameters[5] = params[5];
	this->parameters[6] = params[6];
	this->parameters[7] = params[7];
	this->parameters[8] = params[8];
}
