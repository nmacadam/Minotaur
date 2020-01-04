#include "Window.h"
#include <iostream>
#include <GL/glew.h>

Window::Window()
{

}

Window::~Window()
{
	SDL_DestroyWindow(window);
	window = nullptr;
}

int Window::create(std::string title, int screenWidth, int screenHeight, unsigned currentFlags)
{
	bool success = true;

	Uint32 flags = SDL_WINDOW_OPENGL;

	if (currentFlags & INVISIBLE) flags |= SDL_WINDOW_HIDDEN;
	if (currentFlags & FULLSCREEN) flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
	if (currentFlags & BORDERLESS) flags |= SDL_WINDOW_BORDERLESS;

	//Create window
	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, flags);//SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		std::cerr << "Window could not be created: " << SDL_GetError() << "\n";
		success = false;
	}
	else
	{
		//Create OpenGL Context
		glContext = SDL_GL_CreateContext(window);
		if (glContext == nullptr)
		{
			std::cerr << "GL context could not be created: " << SDL_GetError() << "\n";
		}
		else std::cout << "GL Context created" << std::endl;

		//Start glew
		glewExperimental = true;
		GLenum error = glewInit();
		if (error != GLEW_OK)
		{
			//throw error glewGetErrorString(error);
			std::cerr << "GLEW could not be initialized: " << (const char*)glewGetErrorString(error) << "\n";
		}
		else std::cout << "GLEW initialized successfully" << std::endl;

		std::cout << "Using OpenGL " << glGetString(GL_VERSION) << std::endl;
	}

	glClearColor(0, 0, 1, 1.0);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	return success;
}

void Window::swapBuffer()
{
	SDL_GL_SwapWindow(window);
}

SDL_Window* Window::getSDLWindow() const
{
	return window;
}

SDL_GLContext Window::getGLContext() const
{
	return glContext;
}
