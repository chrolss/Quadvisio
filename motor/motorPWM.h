#ifndef MOTORPWM_H_
#define MOTORPWM_H_

class motorPWM
{
public:
	motorPWM();
	void setMotorPWM(double s1, double s2, double s3, double s4); //will take 4 speed values and write correct PWM
	void talk(int argc, char** argv); //test function for pyscripts
	~motorPWM();

private:
	double p1,p2,p3,p4;
};

#endif /* MOTORPWM_H_ */	
 
