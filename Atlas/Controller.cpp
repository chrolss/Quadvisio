//
//  Controller.cpp
//  Atlas Software
//
//  Created by Quadvisio on 2014-06-06 as part of the Atlas Project.
//  Copyright (c) 2014 Quadvisio. All rights reserved.
//

#include "Controller.h"


Controller::Controller(){
    this->ea[1] = 0.0;
    this->eb[1] = 0.0;
    this->eg[1]	= 0.0;
    this->ea[2] = 0.0;
    this->eb[2] = 0.0;
    this->eg[2] = 0.0;
}

void Controller::calcPWM(double *input, double *output) {
	/*
    for (int i=3; i<6; i++) {
        std::cout << "Rad: " << input[i] << " ";
    }
    std::cout << std::endl;
	*/

    //alphadelen
	ea[0] = refs[0] - input[3];  	// set new error
	this->ea[2] += ea[0]*dt;
	if (abs(ea[2])>WINDUP_LIMIT_UP){
		ea[2] = windUp(ea);
	}
	MaT = parameters[0]*ea[0] + parameters[1]*(ea[2]) + parameters[2]*(ea[0]-ea[1])/dt;
	//printf("D: %f, ea0: %f, ea1: %f, eD: %f\n", parameters[2]*(ea[0]-ea[1])/dt,ea[0],ea[1],(ea[0]-ea[1]));
	this->ea[1] = ea[0];		// set old error

	//printf("P: %f, I: %f, D: %f, e0: %f, e2: %f\n",parameters[0]*ea[0], parameters[1]*(ea[2]), parameters[2]*(ea[0]-ea[1])/dt,ea[0],ea[2]);
	//betadelen
	eb[0] = refs[1] - input[4];  	// set new error
	this->eb[2] += eb[0]*dt;
	if (abs(eb[2])>WINDUP_LIMIT_UP){
		eb[2] = windUp(eb);
	}
	MbT = parameters[3]*eb[0] + parameters[4]*(eb[2]) + parameters[5]*(eb[0]-eb[1])/dt;
	this->eb[1] = eb[0];		// set old error

	//printf("P: %f, I: %f, D: %f, e: %f\n",parameters[3]*eb[0], parameters[4]*(eb[2]), parameters[5]*(eb[0]-eb[1])/dt,eb[0]);
	//printf("rollfel: %f, pitchfel: %f\n",ea[2],eb[2]);

	//gammadelen
	eg[0] = refs[2] - input[5];  	// set new error
	this->eg[2] += eg[0]*dt;
	if (abs(eg[2])>WINDUP_LIMIT_UP){
		eg[2] = windUp(eg);
	}
	Mg = parameters[6]*eg[0] + parameters[7]*(eg[2]) + parameters[8]*(eg[0]-eg[1])/dt;
	this->eg[1] = eg[0];		// set old error

	//printf("P: %f, I: %f, D: %f, e: %f\n",parameters[6]*eg[0], parameters[7]*(eg[2]), parameters[8]*(eg[0]-eg[1])/dt,eg[0]);

    //printf("MaT: %f, MbT: %f\n", MaT, MbT);
    Ma = (MaT*COS45 - MbT*SIN45);
    Mb = (MaT*COS45 + MbT*COS45);
    Mg = 0.0;
    printf("Ma = %f, Mb = %f, Mg = %f, F = %f \n", Ma, Mb, Mg, F);
    output[0] = 0.25*(F*CONST1 + Mb*CONST2 + Mg*CONST3);
    output[1] = 0.25*(F*CONST1 - Ma*CONST2 - Mg*CONST3);
    output[2] = 0.25*(F*CONST1 - Mb*CONST2 + Mg*CONST3);
    output[3] = 0.25*(F*CONST1 + Ma*CONST2 - Mg*CONST3);
    
    //printf("Before saturation \n");
    //printf("LF = %f, RF = %f, RR = %f, RL = %f \n", output[0], output[1],output[2], output[3]);

    // Make sure output is between 0-max percentage
    for (int i=0; i<4; i++) {
        if (output[i]<0) {
            output[i]=0.0;
        }
        output[i]=sqrt(output[i]);
        //printf("Squared value: %f", output[i]);
        if (output[i]>MAX_PERCENTAGE) {
            output[i]=MAX_PERCENTAGE;
        }
    }
    printf("LF = %f, RF = %f, RR = %f, LR = %f \n", output[0], output[1],output[2], output[3]);

}

void Controller::setReference(double *ref){
	this->refs[0] = ref[0];		//roll
	this->refs[1] = ref[1];		//pitch
	this->refs[2] = ref[2];		//yaw
	this->refs[3] = ref[3];		//x-acceleration
	this->refs[4] = ref[4];		//y-acceleration
	this->refs[5] = ref[5];		//z-acceleration
	this->refs[6] = ref[6];		//altitude

}

void Controller::setThrust(int _thrust){
	this->F = 4*THRUST_CONSTANT*_thrust*_thrust; 		//Toni fixar denna rad
}

double Controller::windUp(double *err){
		if (err[2]>0){
			return WINDUP_LIMIT_UP;
		}
		else{
			return WINDUP_LIMIT_DOWN;

			}
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
