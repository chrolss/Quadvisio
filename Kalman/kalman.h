//
//  kalman.h
//  Atlas Software
//
//  Created by Quadvisio on 2014-06-20 as part of the Atlas Project.
//  Copyright (c) 2014 Quadvisio. All rights reserved.
//

#ifndef KALMAN_H_
#define KALMAN_H_

#include <iostream>
#include <math.h>

class kalman
{
public:
	kalman();
	double estimate(double val);
	void setFilter(double q, double r, double _x0, double _p0);
private:
	double q; //process noise covariange
	double r; //measurement noise covariance
	double x; //predicted state
	double p; //estimation error covariance
	double k; //Kalman gain
	double x0; //previous predicted state
	double p0; //previous predicted error covariance



};

#endif /*KALMAN_H_ */
