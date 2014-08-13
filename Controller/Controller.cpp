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
    //alphadelen
	ea[0] = refs[0] - input[3];  	// set new error
	this->ea[2] += ea[0]*dt;
	Ma = parameters[0]*ea[0] + parameters[1]*(ea[2]) + parameters[2]*(ea[0]-ea[1]);
	ea[0] = this->ea[1];		// set old error

	//betadelen
	eb[0] = refs[1] - input[4];  	// set new error
	this->eb[2] += eb[0]*dt;
	Mb = parameters[3]*eb[0] + parameters[4]*(eb[2]) + parameters[5]*(eb[0]-eb[1]);
	eb[0] = this->eb[1];		// set old error

	//gammadelen
	eg[0] = refs[2] - input[5];  	// set new error
	this->eg[2] += eg[0]*dt;
	Mg = parameters[6]*eg[0] + parameters[7]*(eg[2]) + parameters[8]*(eg[0]-eg[1]);
	eg[0] = this->eg[1];		// set old error


	printf("Ma = %f, Mb = %f, Mg = %f, F = %f \n", Ma, Mb, Mg, F);

    output[0] = (1/(4*THRUST_CONSTANT))*(F+Ma+Mb+Mg);
    output[1] = (1/(2*THRUST_CONSTANT*ARM_RADIUS))*(Ma+Mg);
    output[2] = (1/(2*THRUST_CONSTANT*ARM_RADIUS))*(F-Mb);
    output[3] = (1/(4*DRAG_CONSTANT))*(F-Ma+Mb-Mg);
    
}

void Controller::setReference(double *ref){
	this->refs[0] = ref[0];
	this->refs[1] = ref[1];
	this->refs[2] = ref[2];
}

void Controller::setF(double _thrust){
	this->F = _thrust; 		//Toni fixar denna rad
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
