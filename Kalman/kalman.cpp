#include "kalman.h"

kalman::kalman(double _q, double _r, double _x, double _p){
	this->q =_q;
	this->r = _r;
	this->x = _x;
	this->p = _p;
}
