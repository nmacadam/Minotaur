#pragma once
#include "../ECS/ECS.h"
#include "../ECS/Transform.h"
#include "../ECS/Camera.h"
#include "HeadBob.h"

class PlayerController : public Component
{
public:
	PlayerController(float moveSpeed) : moveSpeed(moveSpeed) {};
	
	void initialize() override;
	void update() override;
	void draw() override;
	
	void drawEditor() override;
	
	~PlayerController() override;
private:
	Camera* camera;
	HeadBob* headBob;
	Transform* transform;
	float moveSpeed;
};
