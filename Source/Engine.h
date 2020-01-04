#pragma once
#include "Window.h"
#include <stack>
#include "GameState.h"
#include "ECS/ECS.h"

class Engine
{
public:
	Engine();
	~Engine();

	bool initialize(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	void handleEvents();
	void update();
	void render();

	void changeState(GameState* state);
	void pushState(GameState* state);
	void popState(GameState* state);
	GameState* peekState();

	void clean();

	Window window = Window();

	static const int SCREEN_WIDTH = 1200;
	static const int SCREEN_HEIGHT = 800;

	bool isRunning = false;

	static unsigned int framebuffer;
	static unsigned int textureColorbuffer;

	static EntitySet* loadedEntities;
	
private:
	bool vsync = true;
	std::stack<GameState*> stateStack;
};