//
//  Controller.cpp
//  Atlas Software
//
//  Created by Quadvisio on 2014-06-06 as part of the Atlas Project.
//  Copyright (c) 2014 Quadvisio. All rights reserved.
//

#include "Controller.h"


Controller::Controller(bool bird){
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
    this->joyCom[0] = 0.0;
    this->joyCom[1] = 0.0;
    this->joyCom[2] = 0.0;
    this->dB = 0.0;
    this->dA = 0.0;

    birdSetup(bird);
    get_Parameters();
}

void Controller::birdSetup(bool _bird){
	if (_bird){
		this->k1 = CONST1;
		this->k2 = CONST2;
		this->k3 = CONST3;
		this->pigeon = true;
		printf("Pigeon selected, initilizing system\n");
	}
	else{
		this->k1 = CONST4;
		this->k2 = CONST5;
		this->k3 = CONST6;
		this->pigeon = false;
		printf("Phoenix selected, initilizing system\n");
	}
}

//reads PID parameters from two txt-files and sets them
void Controller::get_Parameters(){
	std::fstream params1("innerParameters.txt");
	params1 >> this->innerParameters[0] >>  this->innerParameters[1] >>  this->innerParameters[2]
	>>  this->innerParameters[3] >>  this->innerParameters[4] >>  this->innerParameters[5]
	>> this->innerParameters[6] >> this->innerParameters[7] >> this->innerParameters[8]
	>> this->innerParameters[9] >> this->innerParameters[10] >> this->innerParameters[11]
	>> this->trim[0] >> this->trim[1];
	params1.close();
	std::fstream params2("outerParameters.txt");
	params2 >> 	this->outerParameters[0] >> this->outerParameters[1]
	>> this->outerParameters[2] >> this->outerParameters[3]
	>> this->outerParameters[4] >> this->outerParameters[5];
	params2.close();
}

//writes PID parameters back to txt-files
void Controller::write_Parameters(double *inner, double *outer){
	std::ofstream params3;	//for output
	params3.open("innerParameters.txt");
	params3 << inner[0] << "\t" << inner[1] << "\t" << inner[2] << "\t"
	 << inner[3] << "\t" << inner[4] << "\t" << inner[5] << "\t"
	 << inner[6] << "\t" << inner[7] << "\t" << inner[8] << "\t"
	 << inner[9] << "\t" << inner[10] << "\t" << inner[11] << "\t"
	 << trim[0] << "\t" << trim[1];
	params3.close();
	std::ofstream params4;	//for output
	params4 << outer[0] << "\t"  << outer[1] << "\t" << outer[2] << "\t"
	 << outer[3] << "\t" << outer[4] << "\t" << outer[5] << "\t";
	params4.close();

}

void Controller::send_Parameters(double *params){
	for (int i = 0; i < 12; i++){
		params[i] = innerParameters[i];
	}
}

void Controller::reset_I(){
	this->ea[2] = 0.0;
	this->eb[2] = 0.0;
	this->eg[2] = 0.0;
}

void Controller::get_Errors(double *_err){
	_err[0] = ea[2]/WINDUP_LIMIT_UP*100.0;
	_err[1] = eb[2]/WINDUP_LIMIT_UP*100.0;
	_err[2] = eg[2]/WINDUP_LIMIT_UP*100.0;
}

void Controller::calcPWM(double *input, double *output, double *ref) {

	//alphadelen - roll
	ea[0] = ref[0] - input[3] + trim[0];  	// set new error
	this->ea[2] += (ea[0])*dt;
	if (fabs(ea[2])>WINDUP_LIMIT_UP){
		this->ea[2] = windUp(ea);
	}
	MaT = innerParameters[0]*ea[0] + innerParameters[1]*(ea[2]) + innerParameters[2]*(ea[0]-ea[1])/dt;
	//printf("D: %f, ea0: %f, ea1: %f, eD: %f\n", innerParameters[2]*(ea[0]-ea[1])/dt,ea[0],ea[1],(ea[0]-ea[1]));
	this->ea[1] = ea[0];		// set old error

	//printf("P: %f, I: %f, D: %f, e0: %f, e2: %f\n",innerParameters[0]*ea[0], innerParameters[1]*(ea[2]), innerParameters[2]*(ea[0]-ea[1])/dt,ea[0],ea[2]);
	//betadelen - pitch
	eb[0] = ref[1] - input[4] + trim[1];  	// set new error
	this->eb[2] += eb[0]*dt;
	if (fabs(eb[2])>WINDUP_LIMIT_UP){
		this->eb[2] = windUp(eb);
	}
	MbT = innerParameters[3]*eb[0] + innerParameters[4]*(eb[2]) + innerParameters[5]*(eb[0]-eb[1])/dt;
	this->eb[1] = eb[0];		// set old error

	//printf("P: %f, I: %f, D: %f, e: %f\n",innerParameters[3]*eb[0], innerParameters[4]*(eb[2]), innerParameters[5]*(eb[0]-eb[1])/dt,eb[0]);
	//printf("rollfel: %f, pitchfel: %f\n",ea[2],eb[2]);

	//gammadelen
	eg[0] = ref[2] - input[5] + joyCom[2];  	// set new error

	if (fabs(eg[0])>3.84){						//220 degrees
		if (eg[0]>0){
			eg[0] = eg[0] - 2*M_PI;
		}
		else{
			eg[0] = eg[0] + 2*M_PI;
		}
	}

	this->eg[2] += eg[0]*dt;
	if (fabs(eg[2])>WINDUP_LIMIT_UP){
		this->eg[2] = windUp(eg);
	}
	MgT = innerParameters[6]*eg[0] + innerParameters[7]*(eg[2]) + innerParameters[8]*(eg[0]-eg[1])/dt;
	this->eg[1] = eg[0];		// set old error

	//printf("P: %f, I: %f, D: %f, e: %f\n",innerParameters[6]*eg[0], innerParameters[7]*(eg[2]), innerParameters[8]*(eg[0]-eg[1])/dt,eg[0]);

    //printf("MaT: %f, MbT: %f\n", MaT, MbT);
    Ma = (MaT*COS45 - MbT*SIN45);
    Mb = (MaT*COS45 + MbT*COS45);
    Mg = -MgT;		//change stuff

    
    //printf("Ma = %f, Mb = %f, Mg = %f, F = %f \n", Ma, Mb, Mg, F);
    output[0] = 0.25*(F*k1 + Mb*k2 + Mg*k3);
    output[1] = 0.25*(F*k1 - Ma*k2 - Mg*k3);
    output[2] = 0.25*(F*k1 - Mb*k2 + Mg*k3);
    output[3] = 0.25*(F*k1 + Ma*k2 - Mg*k3);


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
    //printf("LF = %f, RF = %f, RR = %f, LR = %f \n", output[0], output[1],output[2], output[3]);

}


void Controller::calcRef(double *sensorInput, double *ref){
	//Read ref 3 and 4  + accInput 0 and 1, while returning ref 0 and 1
	//compensate accInput 0 and 1 with accInput 3 and 4 (alpha and beta angles)
	ex[0] = ref[3] - cos(sensorInput[4])*(sensorInput[0]-sin(sensorInput[4]));	//x-acc error
	this->ex[2] += ex[0]/dt;		//store error in I-summation
	dB = outerParameters[0]*ex[0] + outerParameters[1]*(ex[2]) + outerParameters[2]*(ex[0]-ex[1]);
	this->ex[1] = ex[0];
	//printf("ex0: %f, ax: %f, dB: %f\n", ex[0],cos(sensorInput[4])*sensorInput[0], dB);
	ey[0] = ref[4] - cos(sensorInput[3])*(sensorInput[1]-sin(sensorInput[3]));	//y-acc error
	this->ey[2] += ey[0]/dt;		//store error in I-summation
	dA = outerParameters[3]*ey[0] + outerParameters[4]*(ey[2]) + outerParameters[5]*(ey[0]-ey[1]);
	this->ey[1] = ey[0];

	ref[0] = -dA;
	ref[1] = -dB;
}

void Controller::setJoyCom(double *joy, double *sensorInput, double *ref){
	if (fabs(joy[2])>0){					//this will hopefully reset the yaw reference
		setYawRef(ref, sensorInput[5]);	//to the current yaw input from the sensor
	}									//so the reference won't interfere with the controller
	/*
	if (fabs(joy[3])<0.1){
		//reset_PID();			//if the throttle is lower than 0.1 the I parameters in the
	}							//PID will be set to zero
	*/
	this->F = 4*THRUST_CONSTANT*joy[3]*joy[3]*10000.0;
	setSensitivity(joy[6]);
	ref[0] = sens*joy[0];
	ref[1] = -sens*joy[1];
	this->joyCom[2] = sens*joy[2];
	this->trim[0] = joy[4];	//add from *joy
	this->trim[1] = -joy[5];	//add from *joy


}

void Controller::setSensitivity(double _sens){
	this->sens = _sens;
}

void Controller::setYawRef(double *ref, double _yaw){
	ref[2] = _yaw;
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
	this->innerParameters[9] = inParams[9];
	this->innerParameters[9] = inParams[10];
	this->innerParameters[9] = inParams[11];

}

void Controller::setOuterParameters(double *outParams){
	this->outerParameters[0] = outParams[0];
	this->outerParameters[1] = outParams[1];
	this->outerParameters[2] = outParams[2];
	this->outerParameters[3] = outParams[3];
	this->outerParameters[4] = outParams[4];
	this->outerParameters[5] = outParams[5];
}

