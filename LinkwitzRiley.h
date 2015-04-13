#pragma once
#include "pluginconstants.h"

//implements a second order linkwitz-riley filter, either as lowpass or highpass, for use in crossovers and multiband systems. 
class CLinkwitzRiley
{
public:
	CLinkwitzRiley();
	virtual ~CLinkwitzRiley();
	void setType(UINT u){ type = u; }
	void setCutoff(float f){ cutoff = f; }
	void setSampleRate(int f){ sampleRate = f; }
	float doFilter(float input);
protected:
	UINT type;
	/* Use these codes
	type = 0 : Lowpass
	type = 1 : Highpass
	*/
	void flushDelays();
	float cutoff;
	void calcCoefficients(float fc, UINT type);
	float theta_c;
	float omega_c;
	float k;
	float delta;
	float a0;
	float a1;
	float a2;
	float b1;
	float b2;
	int sampleRate;
	float xn;
	float yn;
	float xn_1;
	float xn_2;
	float yn_1;
	float yn_2;
};
