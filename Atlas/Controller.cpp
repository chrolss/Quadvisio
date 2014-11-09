//
//  Controller.cpp
//  Atlas Software
//
//  Created by Quadvisio on 2014-06-06 as part of the Atlas Project.
//  Copyright (c) 2014 Quadvisio. All rights reserved.
//

#include "Controller.h"


Controller::Controller(bool bird){
    this->err_roll[1] = 0.0;
    this->err_pitch[1] = 0.0;
    this->err_yaw[1]	= 0.0;
    this->err_roll[2] = 0.0;
    this->err_pitch[2] = 0.0;
    this->err_yaw[2] = 0.0;
    this->err_alt[0] = 0.0;
    this->err_alt[1] = 0.0;
    this->err_alt[2] = 0.0;
    this->ex[1] = 0.0;
    this->ey[1] = 0.0;
    this->ex[2] = 0.0;
    this->ey[2] = 0.0;
    this->joyCom[0] = 0.0;
    this->joyCom[1] = 0.0;
    this->joyCom[2] = 0.0;
    this->dB = 0.0;
    this->dA = 0.0;
    
    alt_hold = false;

    birdSetup(bird);
    read_parameters(bird_params_file);
}

void Controller::birdSetup(bool _bird){
	if (_bird){
        this->thrust_const = THRUST_CONSTANT_PIGEON;
		this->pigeon = true;
		this->bird_params_file = "innerParameters_pigeon.txt";
		printf("Pigeon selected, initilizing system\n");
	}
	else{
        this->thrust_const = THRUST_CONSTANT_PHOENIX;
		this->pigeon = false;
		this->bird_params_file = "innerParameters_phoenix.txt";
		printf("Phoenix selected, initilizing system\n");
	}
}

//reads PID parameters from two txt-files and sets them
void Controller::read_parameters(std::string _birdParams){
	std::fstream paramsFile(_birdParams);
    std::string line;
    int i = 0;
    if (paramsFile.is_open()) {
        while (getline(paramsFile, line)) {
            innerParameters[i] = atof(line.c_str());
            i++;
        }
    }
    else {
        printf("Error reading innerParameters.txt");
    }

	paramsFile.close();
	printf("Got Parameters\n");
}

//writes PID parameters back to txt-files
void Controller::write_Parameters(double *inner, double *outer){
	std::ofstream paramsFile;	//for output
	paramsFile.open(bird_params_file);

    if (paramsFile.is_open()) {
        paramsFile << inner[0] << "\n" << inner[1] << "\n" << inner[2] << "\n"
        << inner[3] << "\n" << inner[4] << "\n" << inner[5] << "\n"
        << inner[6] << "\n" << inner[7] << "\n" << inner[8] << "\n"
        << inner[9] << "\n" << inner[10] << "\n" << inner[11] << "\n"
        << inner[12] << "\n" << inner[13] << "\n" << inner[14] << "\n" << inner[15];
        paramsFile.close();
        
        printf("Parameters Written\n");
    }
	
    else {
        printf("Error writing to innerParameters.txt");
    }
}

void Controller::get_parameters(double *params){
	for (int i = 0; i < 16; i++){
		params[i] = innerParameters[i];
	}
}

void Controller::reset_I(){
	this->err_roll[2] = 0.0;
	this->err_pitch[2] = 0.0;
	this->err_yaw[2] = 0.0;
    this->err_alt[2] = 0.0;
}

void Controller::get_Errors(double *_err){
	_err[0] = err_roll[2]/WINDUP_LIMIT_UP*100.0;
	_err[1] = err_pitch[2]/WINDUP_LIMIT_UP*100.0;
	_err[2] = err_yaw[2]/WINDUP_LIMIT_UP*100.0;
}

void Controller::calcPWM(double *input, double *output, double *ref) {

	// Roll
	err_roll[0] = ref[0] - input[3] + innerParameters[12];  	// set new error
	err_roll[2] += (err_roll[0])*dt;
	if (fabs(err_roll[2])>WINDUP_LIMIT_UP){
		err_roll[2] = windUp(err_roll);
	}
	MomRollTemp = innerParameters[0]*err_roll[0] + innerParameters[1]*(err_roll[2]) + innerParameters[2]*(err_roll[0]-err_roll[1])/dt;
	//printf("D: %f, ea0: %f, ea1: %f, eD: %f\n", innerParameters[2]*(ea[0]-ea[1])/dt,ea[0],ea[1],(ea[0]-ea[1]));
	err_roll[1] = err_roll[0];		// set old error

	// Pitch
	err_pitch[0] = ref[1] - input[4] + innerParameters[13];  	// set new error
	err_pitch[2] += err_pitch[0]*dt;
	if (fabs(err_pitch[2])>WINDUP_LIMIT_UP){
		err_pitch[2] = windUp(err_pitch);
	}
	MomPitchTemp = innerParameters[3]*err_pitch[0] + innerParameters[4]*(err_pitch[2]) + innerParameters[5]*(err_pitch[0]-err_pitch[1])/dt;
	err_pitch[1] = err_pitch[0];		// set old error


	// Yaw
	err_yaw[0] = ref[2] - input[5] + joyCom[2];  	// set new error

	if (fabs(err_yaw[0])>3.84){						//220 degrees
		if (err_yaw[0]>0){
			err_yaw[0] = err_yaw[0] - 2*M_PI;
		}
		else{
			err_yaw[0] = err_yaw[0] + 2*M_PI;
		}
	}

	this->err_yaw[2] += err_yaw[0]*dt;
	if (fabs(err_yaw[2])>WINDUP_LIMIT_UP){
		this->err_yaw[2] = windUp(err_yaw);
	}
	MomYawTemp = innerParameters[6]*err_yaw[0] + innerParameters[7]*(err_yaw[2]) + innerParameters[8]*(err_yaw[0]-err_yaw[1])/dt;
	err_yaw[1] = err_yaw[0];		// set old error

	//printf("P: %f, I: %f, D: %f, e: %f\n",innerParameters[6]*eg[0], innerParameters[7]*(eg[2]), innerParameters[8]*(eg[0]-eg[1])/dt,eg[0]);
    
    // Altitude PID
    if (this->alt_hold) {
        err_alt[0] = ref[6] - input[6];  	// set new error
        
        // Limit the error to avoid nervous behavior
        if (err_alt[0] > 2.0) {
            err_alt[0] = 2.0;
        }
        else if(err_alt[0] < -2.0) {
            err_alt[0] = -2.0;
        }
        
        err_alt[2] += err_alt[0]*dt;
        
        printf("alt err: %f\n", err_alt[0]);
        
        //if (fabs(err_alt[2])>WINDUP_LIMIT_UP){err_alt[2] = windUp(err_alt);}
        
        vertThrust = innerParameters[9]*err_alt[0] + innerParameters[10]*(err_alt[2]) + innerParameters[11]*(err_alt[0]-err_alt[1])/dt;
        err_alt[1] = err_alt[0];
    
        F = vertThrust + 4*thrust_const*0.30*0.30*10000.0;
    }
    
    if (pigeon) {
        //printf("MaT: %f, MbT: %f\n", MaT, MbT);
        Ma = (MomRollTemp*COS45 - MomPitchTemp*SIN45);
        Mb = (MomRollTemp*COS45 + MomPitchTemp*COS45);
        Mg = -MomYawTemp;		//change stuff
        
        //printf("Ma = %f, Mb = %f, Mg = %f, F = %f \n", Ma, Mb, Mg, F);
        output[0] = 0.25*(F*CONST1 + Mb*CONST2 + Mg*CONST3);
        output[1] = 0.25*(F*CONST1 - Ma*CONST2 - Mg*CONST3);
        output[2] = 0.25*(F*CONST1 - Mb*CONST2 + Mg*CONST3);
        output[3] = 0.25*(F*CONST1 + Ma*CONST2 - Mg*CONST3);
    }
    
    else {
        Mb = -MomPitchTemp;
    	Mg = -MomYawTemp;
    	
        output[0] = F*CONST4 + MomRollTemp*CONST5 - Mb*CONST6 + Mg*CONST7;
        output[1] = F*CONST4 - MomRollTemp*CONST5 - Mb*CONST6 - Mg*CONST7;
        output[2] = F*CONST4 - MomRollTemp*CONST5 + Mb*CONST6 + Mg*CONST7;
        output[3] = F*CONST4 + MomRollTemp*CONST5 + Mb*CONST6 - Mg*CONST7;
    }

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
		setYawRef(ref, sensorInput[5]);     //to the current yaw input from the sensor
	}                                       //so the reference won't interfere with the controller
    
    if (!alt_hold) {
        this->F = 4*thrust_const*joy[3]*joy[3]*10000.0;
    }
	
    if (joy[4]>-900){
		setSensitivity(joy[6]);
		this->innerParameters[12] = joy[4];	//add from *joy
		this->innerParameters[13] = -joy[5];	//add from *joy
	}
    
	ref[0] = innerParameters[14]*joy[0];
	ref[1] = -innerParameters[14]*joy[1];
	this->joyCom[2] = 2.0*innerParameters[15]*joy[2];
}

void Controller::setSensitivity(double _sens){
	this->innerParameters[14] = _sens;
}

void Controller::setYawRef(double *ref, double _yaw){
	ref[2] = _yaw;
}

double Controller::windUp(double *err){
		if (err[2]>0){return WINDUP_LIMIT_UP;}
		else{return WINDUP_LIMIT_DOWN;}
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
	this->innerParameters[10] = inParams[10];
	this->innerParameters[11] = inParams[11];
	this->innerParameters[12] = inParams[12];
	this->innerParameters[13] = inParams[13];
	this->innerParameters[14] = inParams[14];
    this->innerParameters[15] = inParams[15];

}

void Controller::setOuterParameters(double *outParams){
	this->outerParameters[0] = outParams[0];
	this->outerParameters[1] = outParams[1];
	this->outerParameters[2] = outParams[2];
	this->outerParameters[3] = outParams[3];
	this->outerParameters[4] = outParams[4];
	this->outerParameters[5] = outParams[5];
}

double Controller::getCurrentThrust() {
    
    double thrust = sqrt((F)/(thrust_const*40000.0));
    std::cout << thrust << std::endl;
    if (thrust>1.0) {
        thrust = 1.0
    }
    return thrust;
}

