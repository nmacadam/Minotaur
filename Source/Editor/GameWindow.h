#pragma once
#include "EditorWindow.h"
#include "../Texture.h"

class GameWindow :
	public EditorWindow
{
public:
	void render(Engine* engine) override;

	Texture* diffuseMap = nullptr;
};

