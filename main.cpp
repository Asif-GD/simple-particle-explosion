#include "Screen.h"
#include "ColorGradient.h"
#include "Particle.h"
#include "Swarm.h"

#include <stdlib.h>
#include <time.h>

int main(int argc, char* argv[]) {

	srand(time(NULL));

	const int HALF_WINDOW_WIDTH = Screen::WINDOW_WIDTH / 2;
	const int HALF_WINDOW_HEIGHT = Screen::WINDOW_HEIGHT / 2;

	Screen screen;
	ColorGradient gradient;
	Swarm swarm;

	if (screen.init() == false)
		std::cout << "SDL Initialization Failed" << std::endl;

	bool is_running = true;
	int ticks;

	//game loop
	while (is_running) {

		ticks = SDL_GetTicks();
		gradient.animateColors(ticks);

		//screen.screenClear();
		swarm.updateSwarm(ticks);

		const Particle* const pParticle = swarm.getParticles();

		for (auto i = 0; i < Swarm::N_PARTICLES; i++)
		{
			Particle particle = pParticle[i];

			int x = (particle.m_xPosition + 1) * HALF_WINDOW_WIDTH;
			int y = particle.m_yPosition * HALF_WINDOW_WIDTH + HALF_WINDOW_HEIGHT;

			screen.setPixelColor(x, y, gradient.red, gradient.green, gradient.blue);
		}

		screen.boxBlur();
		screen.draw();
		
		if (screen.processEvent() == true)
			break;
	}

	screen.close();
	return 0;
}