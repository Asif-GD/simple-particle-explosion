#include "Particle.h"

Particle::Particle() : m_xPosition(0), m_yPosition(0)
{
	init();
}

Particle::~Particle()
{
}

void Particle::init() {

	m_xPosition = 0;
	m_yPosition = 0;
	m_Direction = (2 * M_PI * rand()) / RAND_MAX;
	m_Speed = (0.03 * rand()) / RAND_MAX;

	m_Speed *= m_Speed;
}

void Particle::animateParticle(int interval) {

	m_Direction += interval * 0.0004;

	double xSpeed = m_Speed * cos(m_Direction);
	double ySpeed = m_Speed * sin(m_Direction);

	m_xPosition += xSpeed * interval;
	m_yPosition += ySpeed * interval;

	if (m_xPosition < -1 || m_xPosition > 1 || m_yPosition < -1 || m_yPosition > 1)
		init();

	if (rand() < RAND_MAX / 100)
		init();
}