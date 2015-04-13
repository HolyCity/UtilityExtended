#include "LinkwitzRiley.h"


CLinkwitzRiley::CLinkwitzRiley()
{
	cutoff = 100;
	type = 0;
	xn = 0;
	yn = 0;
	flushDelays();
	sampleRate = 44100;
}
void CLinkwitzRiley::flushDelays()
{
	xn_1 = 0;
	xn_2 = 0;
	yn_1 = 0;
	yn_2 = 0;
}
CLinkwitzRiley::~CLinkwitzRiley()
{
}

float CLinkwitzRiley::doFilter(float input)
{
	xn = input;
	calcCoefficients(cutoff, type);
	yn = a0*xn + a1*xn_1 + a2*xn_2 - b1*yn_1 - b2*yn_2;

	//shuffle delays
	xn_2 = xn_1;
	xn_1 = xn;
	yn_2 = yn_1;
	yn_1 = yn;

	//return output
	return yn;
}

void CLinkwitzRiley::calcCoefficients(float fc, UINT type)
{
	switch (type)
	{
		case 0: //lowpass
		{
			theta_c = pi*cutoff / (float)sampleRate;
			omega_c = pi*fc;
			float omega_c_squared = omega_c*omega_c;
			k = omega_c / tanf(theta_c);

			float k_squared = k * k;
			float denominator = k_squared + omega_c_squared + 2.0 * k * omega_c;

			float b1_num = -2.0*k_squared + 2.0*omega_c_squared;
			float b2_num = -2.0*k*omega_c + k_squared + omega_c_squared;
			a0 = omega_c_squared / denominator;
			a1 = 2.0*omega_c_squared / denominator;
			a2 = a0;
			b1 = b1_num / denominator;
			b2 = b2_num / denominator;

			/*delta = k_squared + omega_c_squared + 2 * k * omega_c;
			a0 = omega_c_squared / delta;
			a1 = 2 * (omega_c_squared / delta);
			a2 = omega_c_squared / delta;
			b1 = (-2 * k_squared + 2 * omega_c_squared) / delta;
			b2 = (-2 * k*omega_c + k_squared + omega_c_squared) / delta;*/

			break;
		}
		case 1: //highpass
		{
			theta_c = pi*cutoff / (float)sampleRate;
			omega_c = pi*fc;
			float omega_c_squared = omega_c*omega_c;
			k = omega_c / tanf(theta_c);

			float k_squared = k * k;
			float denominator = k_squared + omega_c_squared + 2.0 * k * omega_c;

			float b1_num = -2.0*k_squared + 2.0*omega_c_squared;
			float b2_num = -2.0*k*omega_c + k_squared + omega_c_squared;

			a0 = k_squared / denominator;
			a1 = -2.0*k_squared / denominator;
			a2 = a0;
			b1 = b1_num / denominator;
			b2 = b2_num / denominator;
			break;
		}
		default: //lowpass
		{
			theta_c = pi*cutoff / (float)sampleRate;
			omega_c = pi*fc;
			float omega_c_squared = omega_c*omega_c;
			k = omega_c / tanf(theta_c);

			float k_squared = k * k;
			float denominator = k_squared + omega_c_squared + 2.0 * k * omega_c;

			float b1_num = -2.0*k_squared + 2.0*omega_c_squared;
			float b2_num = -2.0*k*omega_c + k_squared + omega_c_squared;
			a0 = omega_c_squared / denominator;
			a1 = 2.0*omega_c_squared / denominator;
			a2 = a0;
			b1 = b1_num / denominator;
			b2 = b2_num / denominator;
			break;
		}
	}
}
