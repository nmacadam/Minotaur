#pragma once
#include <SDL.h>
#include "Engine.h"

#define KEYBOARD_SIZE 282

/*	Notes:
 *	+ This is pretty much a singleton; this design choice isn't fantastic for a lot of application choices where input checking is restricted to only a few objects.
 *		In that case, consider passing the Input object by reference to whatever needs it.  However, the nature of this game engine's ECS system means any
 *		number of user-written components could need to check input for any given reason.  Thus, this class is designed as a Singleton for the purpose of
 *		not wanting to expose engine internal references to user projects.
 *
 *	+ Some optimizations could be made here.  The Input update function is looped into the Engine handleEvents function.  The two functions both read the full frame event
 *		list from SDL, when technically only one of them needs to.  This could be better.
 * 
 */

class Input
{
public:
	static bool getKey(SDL_Scancode key);
	static bool getKeyDown(SDL_Scancode key);
	static bool getKeyUp(SDL_Scancode key);

private:
	static void refresh();
	static void processEvent(SDL_Event* event);
	
	static const Uint8* keyboard;
	
	static std::bitset<KEYBOARD_SIZE> downStates;
	static std::bitset<KEYBOARD_SIZE> upStates;

	// Allow engine class handleEvents to update input buffers
	friend void Engine::handleEvents();
};
