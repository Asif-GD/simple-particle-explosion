#pragma once

#define _USE_MATH_DEFINES

#include <math.h>
#include <stdlib.h>

class Particle
{
public:
	Particle();
	~Particle();

	void animateParticle(int interval);

public:
	double m_xPosition;
	double m_yPosition;

private:
	double m_Speed;
	double m_Direction;

private:
	void init();

};
