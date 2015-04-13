#include "Allpass.h"


CAllpass::CAllpass()
{
	flushDelays();
	sampleRate = 44100;
	cornerFreq = 1000;
	a = 0.1;
}


CAllpass::~CAllpass()
{
}

void CAllpass::flushDelays()
{
	x = 0;
	y = 0;
	x_1 = 0;
	y_1 = 0;
}
void CAllpass::calcCoeff()
{
	/*float omega_c = pi * cornerFreq / (float)sampleRate;
	float alpha = tanf(omega_c);
	float beta = 1 / alpha;
	a = (-1.0 - beta) / (a - beta);*/
	a = (1 - cornerFreq) / (1 + cornerFreq);
}
float CAllpass::doFilter(float input)
{
	y = a * x + x_1 - a * y_1;
	return y;
}
