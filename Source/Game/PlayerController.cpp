#include "PlayerController.h"
#include <SDL.h>
#include "../Input.h"
#include <glm/vec2.hpp>
#include "../MTime.h"

void PlayerController::initialize()
{
	if (!entity->hasComponent<Transform>()) entity->addComponent<Transform>();
	transform = &entity->getComponent<Transform>();

	if (!entity->hasComponent<Camera>()) entity->addComponent<Camera>();
	camera = &entity->getComponent<Camera>();

	if (!entity->hasComponent<HeadBob>()) entity->addComponent<HeadBob>();
	headBob = &entity->getComponent<HeadBob>();
}

void PlayerController::update()
{
	//// Mouse input
	//int xpos = 0;
	//int ypos = 0;
	//SDL_GetRelativeMouseState(&xpos, &ypos);

	//float xoffset = (float)xpos;
	//float yoffset = (float)ypos;
	//float MouseSensitivity = 0.1f;

	//xoffset *= MouseSensitivity;
	//yoffset *= MouseSensitivity;

	//camera->transform->rotation.y += xoffset;
	//camera->transform->rotation.x += yoffset;

	//bool constrainPitch = true;

	//// Make sure that when pitch is out of bounds, screen doesn't get flipped
	//if (constrainPitch)
	//{
	//	if (camera->transform->rotation.x > 89.0f)
	//		camera->transform->rotation.x = 89.0f;
	//	if (camera->transform->rotation.x < -89.0f)
	//		camera->transform->rotation.x = -89.0f;
	//}
	
	// Keyboard input
	glm::vec2 motion(0,0);
	if (Input::getKey(SDL_SCANCODE_W)) motion.x += 1.0f;
	if (Input::getKey(SDL_SCANCODE_S)) motion.x -= 1.0f;
	if (Input::getKey(SDL_SCANCODE_D)) motion.y += 1.0f;
	if (Input::getKey(SDL_SCANCODE_A)) motion.y -= 1.0f;

	camera->transform->rotation.y += motion.y * 3.f;
	
	headBob->movement = motion;

	auto forward = camera->transform->front();
	auto right = camera->transform->right();

	forward.y = 0.f;
	right.y = 0.f;
	forward = glm::normalize(forward);
	right = glm::normalize(right);
	
	float velocity = moveSpeed * MTime::deltaTime;

	auto moveDirection = forward * motion.x;// + right * motion.y;
	
	moveDirection *= velocity;

	transform->position += moveDirection;
	camera->transform->position += moveDirection;
}

void PlayerController::draw()
{
}

void PlayerController::drawEditor()
{
}

PlayerController::~PlayerController()
{
}