#pragma once

#include<iostream>

#include<math.h>

class ColorGradient
{
public:
	ColorGradient();
	~ColorGradient();
	ColorGradient animateColors(int ticks);

public:
	unsigned char red, green, blue;
};
