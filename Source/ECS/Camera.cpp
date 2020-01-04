#include "Camera.h"
#include <glm/ext/quaternion_float.hpp>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include "../Engine.h"

Camera::Camera()
{
}

glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(transform->position, transform->position + transform->front(), transform->up());
}

void Camera::ProcessKeyboard(glm::vec3 movement, float deltaTime)
{
	float velocity = MovementSpeed * deltaTime;
	transform->position += movement * velocity;
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
{
	xoffset *= MouseSensitivity;
	yoffset *= MouseSensitivity;
	
	transform->rotation.y += xoffset;
	transform->rotation.x += yoffset;
	
	// Make sure that when pitch is out of bounds, screen doesn't get flipped
	if (constrainPitch)
	{
	    if (transform->rotation.x > 89.0f)
			transform->rotation.x = 89.0f;
	    if (transform->rotation.x < -89.0f)
			transform->rotation.x = -89.0f;
	}
	
	// Update Front, Right and Up Vectors using the updated Euler angles
	//updateCameraVectors();
}

void Camera::initialize()
{
	// Generate uniform buffer object for camera matrices
	glGenBuffers(1, &UBOMatrices);

	glBindBuffer(GL_UNIFORM_BUFFER, UBOMatrices);
	glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4) + sizeof(glm::vec3), NULL, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	glBindBufferRange(GL_UNIFORM_BUFFER, 0, UBOMatrices, 0, 2 * sizeof(glm::mat4) + sizeof(glm::vec3));

	// Generate UBO for camera position
	/*glGenBuffers(1, &UBOCamera);

	glBindBuffer(GL_UNIFORM_BUFFER, UBOCamera);
	glBufferData(GL_UNIFORM_BUFFER, 1 * sizeof(glm::vec3), NULL, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	glBindBufferRange(GL_UNIFORM_BUFFER, 0, UBOCamera, 0, 1 * sizeof(glm::vec3));*/

	// Get transform component
	if (!entity->hasComponent<Transform>()) entity->addComponent<Transform>();
	transform = &entity->getComponent<Transform>();
}

void Camera::onBeforeDraw()
{
	// Apply projection matrix to uniform buffer
	glm::mat4 projection = glm::perspective(glm::radians(50.f), (float)Engine::SCREEN_WIDTH / (float)Engine::SCREEN_HEIGHT, 0.1f, 100.0f);
	glBindBuffer(GL_UNIFORM_BUFFER, UBOMatrices);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(projection));
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	// Apply view matrix to uniform buffer
	glm::mat4 view = GetViewMatrix();
	glBindBuffer(GL_UNIFORM_BUFFER, UBOMatrices);
	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(view));
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	// Apply camera position to uniform buffer
	glBindBuffer(GL_UNIFORM_BUFFER, UBOCamera);
	glBufferSubData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), sizeof(glm::vec3), glm::value_ptr(transform->position));
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

Camera::~Camera()
{
	glDeleteBuffers(1, &UBOMatrices);
	//glDeleteBuffers(1, &UBOCamera);
}