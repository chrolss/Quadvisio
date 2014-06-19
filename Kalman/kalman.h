#ifndef KALMAN_H
#define KALMAN_H_

#include <iostream>
#include <math.h>

class kalman
{
public:
	kalman(double q, double r, double x, double p);
	double estimate();
private:
	double q; //process noise covariange
	double r; //measurement noise covariance
	double x; //predicted state
	double p; //estimation error covariance
	double k; //Kalman gain
	void setQ(double _q){
		this->q = _q;
	}


};
