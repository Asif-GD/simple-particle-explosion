#include "Screen.h"

Screen::Screen() : m_window(NULL), m_renderer(NULL), m_texture(NULL), m_buffer1(NULL), m_buffer2(NULL) {

	std::cout << "Constructor is called." << std::endl;
}

Screen::~Screen() {

	std::cout << "Destructor is called." << std::endl;
}

bool Screen::init() {

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		SDL_Log("SDL Initialization Failed.", SDL_GetError());
		return false;
	}
	else
		std::cout << "SDL Initialized Successfully." << std::endl;

	m_window = SDL_CreateWindow("Particle Explosion", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);

	if (m_window == NULL)
	{
		SDL_Log("SDL Window Creation Failed", SDL_GetError());
		SDL_Quit();
		return false;
	}
	else
		std::cout << "SDL Window Created Successfully" << std::endl;

	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC);

	if (m_renderer == NULL)
	{
		SDL_Log("SDL Renderer Creation Failed", SDL_GetError());
		SDL_DestroyWindow(m_window);
		SDL_Quit();
		return false;
	}
	else
		std::cout << "SDL Renderer Created Successfully" << std::endl;

	m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, WINDOW_WIDTH, WINDOW_HEIGHT);

	if (m_texture == NULL)
	{
		SDL_Log("SDL Texture Creation Failed", SDL_GetError());
		SDL_DestroyRenderer(m_renderer);
		SDL_DestroyWindow(m_window);
		SDL_Quit();
		return false;
	}
	else
		std::cout << "SDL Texture Created Successfully" << std::endl;

	m_buffer1 = new Uint32[WINDOW_WIDTH*WINDOW_HEIGHT];
	m_buffer2 = new Uint32[WINDOW_WIDTH*WINDOW_HEIGHT];

	memset(m_buffer1, 0x00, WINDOW_WIDTH*WINDOW_HEIGHT * sizeof(Uint32));
	memset(m_buffer2, 0x00, WINDOW_WIDTH*WINDOW_HEIGHT * sizeof(Uint32));

	return true;
}

void Screen::screenClear() {

	memset(m_buffer1, 0x00, WINDOW_WIDTH*WINDOW_HEIGHT * sizeof(Uint32));
	memset(m_buffer2, 0x00, WINDOW_WIDTH*WINDOW_HEIGHT * sizeof(Uint32));
}

void Screen::boxBlur() {

	Uint32* temp = m_buffer1;
	m_buffer1 = m_buffer2;
	m_buffer2 = temp;

	for (auto yPosition = 0; yPosition < WINDOW_HEIGHT; yPosition++) {
		for (auto xPosition = 0; xPosition < WINDOW_WIDTH; xPosition++) {

			int redTotal = 0;
			int greenTotal = 0;
			int blueTotal = 0;

			for (auto row = -1; row <= 1; row++) {
				for (auto column = -1; column <= 1; column++) {

					int currentX = xPosition + column;
					int currentY = yPosition + row;

					if (currentX >= 0 && currentX < WINDOW_WIDTH && currentY >= 0 && currentY < WINDOW_HEIGHT) {

						Uint32 color = m_buffer2[currentY * WINDOW_WIDTH + currentX];

						Uint8 red = color >> 24;
						Uint8 green = color >> 16;
						Uint8 blue = color >> 8;

						redTotal += red;
						greenTotal += green;
						blueTotal += blue;
					}
				}
			}

			Uint8 red = redTotal / 9;
			Uint8 green = greenTotal / 9;
			Uint8 blue = blueTotal / 9;

			setPixelColor(xPosition, yPosition, red, green, blue);
		}
	}
}

void Screen::draw() {

	SDL_UpdateTexture(m_texture, NULL, m_buffer1, WINDOW_WIDTH * sizeof(Uint32));
	SDL_RenderClear(m_renderer);
	SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);
	SDL_RenderPresent(m_renderer);
}

bool Screen::processEvent() {

	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			return true;
		}
		return false;
	}
}

void Screen::setPixelColor(int x, int y, Uint8 red, Uint8 green, Uint8 blue) {

	if (x < 0 || x >= WINDOW_WIDTH || y < 0 || y >= WINDOW_HEIGHT)
		return;

	Uint32 color = 0;

	color += red;
	color <<= 8;
	color += green;
	color <<= 8;
	color += blue;
	color <<= 8;
	color += 0xff;

	m_buffer1[(y * WINDOW_WIDTH) + x] = color;
}

void Screen::close() {

	delete[] m_buffer1;
	delete[] m_buffer2;
	SDL_DestroyTexture(m_texture);
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}
