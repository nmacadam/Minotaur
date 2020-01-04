#include <SDL.h>
#include <iostream>
#include "Engine.h"
#include "MTime.h"
#include "../DeveloperState.h"

int main(int argc, char* args[])
{
    Engine* engine = new Engine();
    DeveloperState* defaultState = new DeveloperState();
	
    if (!engine->initialize("Minotaur Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, engine->SCREEN_WIDTH, engine->SCREEN_HEIGHT, false))
    {
        std::cerr << "Engine failed to initialize!\n";
    }
    else
    {
        engine->changeState(defaultState);

	    while (engine->isRunning)
	    {
            float frameStart = SDL_GetTicks();
	    	
            engine->handleEvents();
            engine->update();
            engine->render();

            MTime::endFrameUpdate(SDL_GetTicks() - frameStart);
	    }
    }

    engine->clean();
    delete defaultState;
    delete engine;
    return 0;
}
