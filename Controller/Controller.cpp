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
    this->ex[1] = 0.0;
    this->ey[1] = 0.0;
    this->ex[2] = 0.0;
    this->ey[2] = 0.0;
    get_Parameters();
}

void Controller::get_Parameters(){
	std::fstream params("parameters.txt");
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
		this->ea[2] = windUp(ea);
	}
	MaT = innerParameters[0]*ea[0] + innerParameters[1]*(ea[2]) + innerParameters[2]*(ea[0]-ea[1])/dt;
	//printf("D: %f, ea0: %f, ea1: %f, eD: %f\n", innerParameters[2]*(ea[0]-ea[1])/dt,ea[0],ea[1],(ea[0]-ea[1]));
	this->ea[1] = ea[0];		// set old error

	printf("P: %f, I: %f, D: %f, e0: %f, e2: %f\n",innerParameters[0]*ea[0], innerParameters[1]*(ea[2]), innerParameters[2]*(ea[0]-ea[1])/dt,ea[0],ea[2]);
	//betadelen
	eb[0] = refs[1] - input[4];  	// set new error
	this->eb[2] += eb[0]*dt;
	if (abs(eb[2])>WINDUP_LIMIT_UP){
		this->eb[2] = windUp(eb);
	}
	MbT = innerParameters[3]*eb[0] + innerParameters[4]*(eb[2]) + innerParameters[5]*(eb[0]-eb[1])/dt;
	this->eb[1] = eb[0];		// set old error

	//printf("P: %f, I: %f, D: %f, e: %f\n",innerParameters[3]*eb[0], innerParameters[4]*(eb[2]), innerParameters[5]*(eb[0]-eb[1])/dt,eb[0]);
	//printf("rollfel: %f, pitchfel: %f\n",ea[2],eb[2]);

	//gammadelen
	eg[0] = refs[2] - input[5];  	// set new error
	this->eg[2] += eg[0]*dt;
	if (abs(eg[2])>WINDUP_LIMIT_UP){
		this->eg[2] = windUp(eg);
	}
	Mg = innerParameters[6]*eg[0] + innerParameters[7]*(eg[2]) + innerParameters[8]*(eg[0]-eg[1])/dt;
	this->eg[1] = eg[0];		// set old error

	//printf("P: %f, I: %f, D: %f, e: %f\n",innerParameters[6]*eg[0], innerParameters[7]*(eg[2]), innerParameters[8]*(eg[0]-eg[1])/dt,eg[0]);

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


void Controller::calcRef(double *accInput, double *refs){
	printf("Här räknar vi ut referensvinklar baserad på accelerationsmätningar\n");
	//Read refs 3 and 4  + accInput 0 and 1, while returning ref 0 and 1
	ex[0] = refs[3] - accInput[0];	//x-acc error
	this->ex[2] += ex[0]/dt;		//store error in I-summation
	dB = outerParameters[0]*ex[0] + outerParameters[1]*(ex[2]) + outerParameters[2]*(ex[0]-ex[1]);
	this->ex[1] = ex[0];

	ey[0] = refs[4] - accInput[1];	//y-acc error
	this->ey[2] += ey[0]/dt;		//store error in I-summation
	dA = outerParameters[3]*ey[0] + outerParameters[4]*(ey[2]) + outerParameters[5]*(ey[0]-ey[1]);
	this->ey[1] = ey[0];

	refs[0] += dA;	//fråga Toni om allt detta
	refs[1] += dB;
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


void Controller::setInnerParameters(double *inParams){
	this->innerParameters[0] = inParams[0];
	this->innerParameters[1] = inParams[1];
	this->innerParameters[2] = inParams[2];
	this->innerParameters[3] = inParams[3];
	this->innerParameters[4] = inParams[4];
	this->innerParameters[5] = inParams[5];
	this->innerParameters[6] = inParams[6];
	this->innerParameters[7] = inParams[7];
	this->innerParameters[8] = inParams[8];
}

void Controller::setOuterParameters(double *outParams){
	this->outerParameters[0] = outParams[0];
	this->outerParameters[1] = outParams[1];
	this->outerParameters[2] = outParams[2];
	this->outerParameters[3] = outParams[3];
	this->outerParameters[4] = outParams[4];
	this->outerParameters[5] = outParams[5];
	this->outerParameters[6] = outParams[6];
	this->outerParameters[7] = outParams[7];
	this->outerParameters[8] = outParams[8];
}
