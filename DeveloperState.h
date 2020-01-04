#pragma once
#include "Source/GameState.h"


class Shader;

class DeveloperState : public GameState
{
private:
	//static DeveloperState instance;

public:
	DeveloperState() {}

	void Initialize(Engine* game);
	void Clean();

	void Pause();
	void Resume();

	void HandleEvents(Engine* game);
	void Update(Engine* game);
	void Render(Engine* game);
	
	/*static DeveloperState* Instance() {
		return &instance;
	}*/
};