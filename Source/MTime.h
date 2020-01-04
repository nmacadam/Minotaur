#pragma once
#include <SDL.h>

class MTime
{
public:
	static float deltaTime;
	static float time;
	static float fps;

	static void endFrameUpdate(float frameDuration)
	{
		frameCount++;
		
		deltaTime = frameDuration / 1000.f;
		time = (float)SDL_GetTicks();

		updateFPS();
	}

private:
	static void updateFPS()
	{
		// reset if 0
		if (startTimer == 0)
		{
			startTimer = SDL_GetTicks();
			deltaFPS = 0;
		}

		// check per second
		frameTimer = SDL_GetTicks() - startTimer;
		deltaFPS++;

		if (frameTimer > 1000)
		{
			fps = (float)deltaFPS / frameTimer * 1000;

			// Error check
			if (fps > 2000000)
			{
				//checks for occasional error that can occur on first frame
				fps = 0;
			}
			else
			{
				// reset
				startTimer = 0;
				deltaFPS = 0;
			}
		}
	}
	
	static int frameCount;
	
	static float startTimer;
	static float frameTimer;
	static int deltaFPS;
};
