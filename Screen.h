#pragma once

#include<iostream>

#include<SDL.h>

class Screen
{
public:
	const static int WINDOW_WIDTH = 1280;
	const static int WINDOW_HEIGHT = 960;

public:
	Screen();
	~Screen();
	bool init();
	void draw();
	bool processEvent();
	void close();
	void setPixelColor(int x, int y, Uint8 red, Uint8 green, Uint8 blue);
	void screenClear();
	void boxBlur();

private:
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
	SDL_Texture* m_texture;
	Uint32* m_buffer1;
	Uint32* m_buffer2;

};
