#include "ColorGradient.h"

ColorGradient::ColorGradient()
{
}

ColorGradient::~ColorGradient()
{
}

ColorGradient ColorGradient::animateColors(int ticks) {

	ColorGradient gradient;

	red = (unsigned char)((1 + sin(ticks * 0.0002)) * 128);
	green = (unsigned char)((1 + sin(ticks * 0.0003)) * 128);
	blue = (unsigned char)((1 + sin(ticks * 0.0004)) * 128);

	return gradient;
}