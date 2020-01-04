#pragma once
#include "Transform.h"

class Light : public Component
{
public:
	Light(glm::vec3 lightColor, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
		: lightColor(lightColor), ambient(ambient), diffuse(diffuse), specular(specular)
	{}

	void initialize() override
	{
		if (!entity->hasComponent<Transform>()) entity->addComponent<Transform>();
		transform = &entity->getComponent<Transform>();
	}
	
	Transform* transform;
	
	glm::vec3 lightColor;
	
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
};

class DirectionalLight : public Light
{
public:
	DirectionalLight(glm::vec3 direction, glm::vec3 lightColor, glm::vec3 ambient, 
		glm::vec3 diffuse, glm::vec3 specular)
		: Light(lightColor, ambient, diffuse, specular), direction(direction)
	{}
	
	glm::vec3 direction;
};

class PointLight : public Light
{
public:
	PointLight(glm::vec3 lightColor, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
		: Light(lightColor, ambient, diffuse, specular), constant(1.0f),
		linear(0.09f), quadratic(0.032f)
	{}
	PointLight(float constant, float linear, float quadratic,
		glm::vec3 lightColor, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
		: Light(lightColor, ambient, diffuse, specular), constant(constant),
			linear(linear), quadratic(quadratic)
	{}
	
	float constant;
	float linear;
	float quadratic;
};

class SpotLight : public DirectionalLight
{
public:
	SpotLight(glm::vec3 direction, float cutOff, glm::vec3 lightColor, 
		glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
		: DirectionalLight(direction, lightColor, ambient, diffuse, specular),
			cutOff(cutOff)
	{}
	
	float cutOff;
};