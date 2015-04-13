#pragma once
#include "pluginconstants.h"
//A one pole all pass filter with variable corner frequency
class CAllpass
{
public:
	CAllpass();
	virtual ~CAllpass();
	void setCorner(float f){ cornerFreq = f; }
	void setSamplerate(int f){ sampleRate = f; }
	void flushDelays();
	void calcCoeff();
	float doFilter(float input);

protected:
	float cornerFreq;
	int sampleRate;
	float x;
	float x_1;
	float y;
	float y_1;
	float a;
};
