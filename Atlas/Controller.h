//
//  Controller.h
//  Atlas Software
//
//  Created by Quadvisio on 2014-06-06 as part of the Atlas Project.
//  Copyright (c) 2014 Quadvisio. All rights reserved.
//

#ifndef __Atlas__Controller__
#define __Atlas__Controller__

#include <iostream>
#include <cstdio>
#include <fstream>
#include <math.h>
#include <cstring>

#define THRUST_CONSTANT 0.0003
#define ARM_RADIUS 0.176
#define DRAG_CONSTANT 9.9768e-8
#define dt 0.017	//påhittad
#define WINDUP_LIMIT_UP 1
#define WINDUP_LIMIT_DOWN -1
#define MAX_PERCENTAGE 80

#define CONST1 3333.33
#define CONST2 37878.7
#define CONST3 1e7

#define COS45 0.7071067812
#define SIN45 0.7071067812

class Controller{
    
public:
    Controller();
    void calcPWM(double *input, double *output, double *ref);
    void calcRef(double *sensorInput, double *ref);
    void setInnerParameters(double *inParams);
    void setOuterParameters(double *outParams);
    void setYawRef(double *ref, double _yaw);
    void setJoyCom(double *joy, double *sensorInput, double *ref);
    double windUp(double *err);
    void write_Parameters(double *inner, double *outer);
    void send_Parameters(double *params);
private:
    void get_Parameters();
    void write_trim();
    double innerParameters[9];
    double outerParameters[9];
    double refs[7];		//roll, pitch, yaw, ax, ay, az, altitude
    double ea[3], eb[3], eg[3];	//angle errors
    double joyCom[3];
    double trim[2];		//trim for roll and pitch
    double ex[3], ey[3];	//acceleration errors
    double F, Ma, Mb, Mg;
    double dA, dB;			//Desired changes in angles
    double MaT, MbT, MgT;
    
};

#endif /* defined(__Atlas__Controller__) */
