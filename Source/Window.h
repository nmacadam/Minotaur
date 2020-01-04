#pragma once
#include <SDL.h>
#include <string>

class Window
{
public:
	Window();
	~Window();

	enum WindowFlags { INVISIBLE = 0x1, FULLSCREEN = 0x2, BORDERLESS = 0x4 };

	int create(std::string title, int screenWidth, int screenHeight, unsigned int currentFlags);
	void swapBuffer();

	int getWidth() { return screenWidth; }
	int getHeight() { return screenHeight; }

	// friend these?
	SDL_Window* getSDLWindow() const;
	SDL_GLContext getGLContext() const;

private:
	SDL_Window* window;
	SDL_GLContext glContext;
	int screenWidth;
	int screenHeight;
};
