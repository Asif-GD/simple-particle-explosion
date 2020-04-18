#pragma once

#include "Particle.h"

class Swarm
{
public:
	const static int N_PARTICLES = 5000;

public:
	Swarm();
	~Swarm();

	const Particle* const getParticles() { return m_pParticles; }
	void updateSwarm(int ticks);

private:
	Particle* m_pParticles;
	int lastTime;
};
