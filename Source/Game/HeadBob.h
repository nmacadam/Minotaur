#pragma once
#include "../ECS/ECS.h"
#include "../ECS/Camera.h"

class HeadBob :
	public Component
{
public:
	HeadBob() = default;
	
	void initialize() override;
	void update() override;
	void draw() override;
	~HeadBob() override;

	void drawEditor() override;
	Camera* camera;

	glm::vec2 movement;

private:
	float timer = 0.0f;
	float bobSpeed = 0.18f;
	float bobAmount = 0.2f;
	float midpoint = 0.5f;

	float waveslice = 0.0f;
};
