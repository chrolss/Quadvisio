//
//  kalman.cpp
//  Atlas Software
//
//  Created by Quadvisio on 2014-06-20 as part of the Atlas Project.
//  Copyright (c) 2014 Quadvisio. All rights reserved.
//

#include "kalman.h"

kalman::kalman(double _q, double _r, double _x0, double _p0){
	this->q =_q;
	this->r = _r;
	this->x0 = _x0;
	this->p0 = _p0;
	std::cout << "Intializing Kalman Filter" << std::endl;
}

void kalman::setFilter(double _q, double _r, double _x0, double _p0){
	this->q =_q;
	this->r = _r;
	this->x0 = _x0;
	this->p0 = _p0;
}

double kalman::estimate(double val){
	x = x0;
	p = p0 + q;
	k = p / (p + r);
	this->x0 = x + k*(val - x);
	this->p0 = (1 - k)*p;
	return x0;

}
