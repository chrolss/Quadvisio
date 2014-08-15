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
#define dt 0.01	//påhittad

#define CONST1 3333.33
#define CONST2 37878
#define CONST3 1e7

#define COS45 0.7071
#define SIN45 0.7071

class Controller{
    
public:
    Controller();
    void calcPWM(double *input, double *output);
    void setParameters(double *params);
    void setReference(double *ref);
    void setF(int _thrust);
private:
    double parameters[9];
    double refs[3];
    double ea[3], eb[3], eg[3];
    double F, Ma, Mb, Mg;
    
};

#endif /* defined(__Atlas__Controller__) */
