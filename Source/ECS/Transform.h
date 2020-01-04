#pragma once
#include "ECS.h"
#include <glm/vec3.hpp>
#include <cereal/cereal.hpp>
#include <glm/ext/quaternion_float.hpp>

class Transform : public Component
{
public:
	Transform(
		glm::vec3 position = glm::vec3(0.f, 0.f, 0.f),
		glm::vec3 rotation = glm::vec3(0.f, 0.f, 0.f),
		glm::vec3 scale = glm::vec3(1.f, 1.f, 1.f)
	);

	glm::vec3 position;
	glm::vec3 rotation; // x: pitch, y: yaw, z: roll
	glm::quat orientation;
	glm::vec3 scale;

	glm::vec3 worldUp = glm::vec3(0, 1, 0);

	glm::vec3 front();
	glm::vec3 right();
	glm::vec3 up();

	glm::mat4 model();

	glm::mat4 getTransformMatrix();

	Transform* parent;
	std::vector<Transform*> children;

	void updateChildren();

	template <class Archive>
	void serialize(Archive& ar)
	{
		ar(cereal::base_class<Component>(this), CEREAL_NVP(position), CEREAL_NVP(rotation), CEREAL_NVP(scale)/*, CEREAL_NVP(children)*/);
	}

	void onBeforeDraw() override;
	void drawEditor() override;
	~Transform() override;

	glm::mat3 transformToMat3(glm::mat4 transform);
	glm::vec3 quatToEuler(glm::quat quat);
};

CEREAL_REGISTER_TYPE(Transform);