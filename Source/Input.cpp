#include "Input.h"

// Define the static member variables
const Uint8* Input::keyboard = nullptr;
std::bitset<KEYBOARD_SIZE> Input::downStates = std::bitset<KEYBOARD_SIZE>(0);
std::bitset<KEYBOARD_SIZE> Input::upStates = std::bitset<KEYBOARD_SIZE>(0);

void Input::refresh()
{
	downStates.reset();
	upStates.reset();

	keyboard = SDL_GetKeyboardState(nullptr);
}

void Input::processEvent(SDL_Event* event)
{
	switch (event->type)
	{
	case SDL_KEYDOWN:
	{
		//keyboard = SDL_GetKeyboardState(nullptr);

		int index = event->key.keysym.scancode;
		downStates.set(index, 1);
	}
	break;

	case SDL_KEYUP:
	{
		//keyboard = SDL_GetKeyboardState(nullptr);

		int index = event->key.keysym.scancode;
		upStates.set(index, 1);
	}
	break;
	}
}

bool Input::getKey(SDL_Scancode key)
{
	return keyboard[key];
}

bool Input::getKeyDown(SDL_Scancode key)
{
	return downStates[key];
}

bool Input::getKeyUp(SDL_Scancode key)
{
	return upStates[key];
}