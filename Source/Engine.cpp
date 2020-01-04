#include "Engine.h"

#include <GL/glew.h>
#include <iostream>
#include "Input.h"

#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "Editor/Editor.h"
#include "../External Libraries/imgui/imgui_impl_sdl.h"

#include <ft2build.h>
#include <freetype/freetype.h>

unsigned int Engine::framebuffer;
unsigned int Engine::textureColorbuffer;

EntitySet* Engine::loadedEntities = nullptr;

Editor* editor;

Engine::Engine(){}
Engine::~Engine(){}

bool Engine::initialize(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    isRunning = false;
	
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << "/n";
        success = false;
    }
    else
    {
        std::cout << "SDL Video and Audio subsystems initialized\n";

    	// Initialize SDL_image
        int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
        if (!(IMG_Init(imgFlags) & imgFlags))
        {
            printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
            success = false;
        }

        // Initialize SDL_ttf
        if (TTF_Init() == -1)
        {
            std::cerr << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << std::endl;
            success = false;
        }
        else std::cout << "SDL_ttf initialized\n";

        // Initialize SDL_mixer
        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
        {
            std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
            success = false;
        }
        else std::cout << "SDL_mixer initialized\n";

        //Vsync enabling (-1 is for adaptive vsync)
        if (!vsync) SDL_GL_SetSwapInterval(0);
        else SDL_GL_SetSwapInterval(-1);

        // Enable double buffer (2 windows, 1 gets drawn, 1 gets cleared, gets rid of flickering)
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

        window.create(title, width, height, 0);

    	// Set OpenGL rendering options
        glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        glFrontFace(GL_CCW);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    editor = new Editor(this);
    editor->initialize();
	
    isRunning = success;
    return success;
}

void Engine::handleEvents()
{
    Input::refresh();

    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {
        Input::processEvent(&event);
        ImGui_ImplSDL2_ProcessEvent(&event);
    	
        switch (event.type) {
        case SDL_QUIT:
            printf("Quitting...\n");
            isRunning = false;
            break;
        default:
            break;
        }
    }

    stateStack.top()->HandleEvents(this);
}

void Engine::update()
{
    stateStack.top()->Update(this);
    editor->update();
}

void Engine::render()
{
    // Clear window
    glClearColor(0.f, 0.f, 0.f, 0.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	// Render
    stateStack.top()->Render(this);
	
    editor->render();
	
	// Swap buffer and flush
    window.swapBuffer();
    glFlush();
}

void Engine::clean()
{
    // cleanup the all states
    while (!stateStack.empty()) {
        stateStack.top()->Clean();
        stateStack.pop();
    }

    editor->clean();
    delete editor;

    Mix_Quit();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void Engine::changeState(GameState* state)
{
    // cleanup the current state
    if (!stateStack.empty()) {
        stateStack.top()->Clean();
        stateStack.pop();
    }

    // store and init the new state
    stateStack.push(state);
    stateStack.top()->Initialize(this);
}

void Engine::pushState(GameState* state)
{
    // pause current state
    if (!stateStack.empty()) {
        stateStack.top()->Clean();
    }

    // store and init the new state
    stateStack.push(state);
    stateStack.top()->Initialize(this);
}

void Engine::popState(GameState* state)
{
    // cleanup the current state
    if (!stateStack.empty()) {
        stateStack.top()->Clean();
        stateStack.push(state);
    }

    // resume previous state
    if (!stateStack.empty()) {
        stateStack.top()->Resume();
    }
}

GameState* Engine::peekState()
{
    // Return null if no states
    if (stateStack.empty())
    {
        std::cout << "State stack empty" << std::endl;
        return nullptr;
    }
    else return stateStack.top();
}