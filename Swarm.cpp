#include "Swarm.h"

Swarm::Swarm() : lastTime(0)
{
	m_pParticles = new Particle[N_PARTICLES];
}

Swarm::~Swarm()
{
	delete[] m_pParticles;
}

void Swarm::updateSwarm(int ticks) {

	int interval = ticks - lastTime;

	for (auto i = 0; i < N_PARTICLES; i++)
	{
		m_pParticles[i].animateParticle(interval);
	}

	lastTime = ticks;
}