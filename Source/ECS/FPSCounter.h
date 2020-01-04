#pragma once
#include "ECS.h"
#include "TextRenderer.h"
#include "../MTime.h"

class FPSCounter :
	public Component
{
public:
	FPSCounter() = default;

	void initialize() override
	{
		if (!entity->hasComponent<TextRenderer>()) std::cerr << "No TextRenderer!\n";//entity->addComponent<TextRenderer>();
		textRenderer = &entity->getComponent<TextRenderer>();
	}
	
	void update() override
	{
		textRenderer->text = std::to_string(MTime::fps);
	}
	
private:
	TextRenderer* textRenderer;
};
