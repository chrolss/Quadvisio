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
#include <math.h>

#define THRUST_CONSTANT 0.0003
#define ARM_RADIUS 0.176
#define DRAG_CONSTANT 9.9768e-8
#define dt 0.02	//påhittad
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
    void calcPWM(double *input, double *output);
    void setParameters(double *params);
    void setReference(double *ref);
    void setThrust(int _thrust);
    double windUp(double *err);
private:
    double parameters[9];
    double refs[7];		//roll, pitch, yaw, ax, ay, az, altitude
    double ea[3], eb[3], eg[3];
    double F, Ma, Mb, Mg;
    double MaT, MbT;
    
};

#endif /* defined(__Atlas__Controller__) */
