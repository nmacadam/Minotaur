#include "Transform.h"
#include <glm/trigonometric.hpp>
#include <glm/geometric.hpp>
#include "../../External Libraries/imgui/imgui.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>
#include "../MMath.h"

Transform::Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
	this->position = position;
	this->rotation = rotation;
	this->scale = scale;
}

glm::vec3 Transform::front()
{
	return glm::normalize(glm::vec3(
		cos(glm::radians(rotation.y)) * cos(glm::radians(rotation.x)),
		sin(glm::radians(rotation.x)),
		sin(glm::radians(rotation.y)) * cos(glm::radians(rotation.x))
	));
}

glm::vec3 Transform::right()
{
	return glm::normalize(glm::cross(front(), worldUp));
}

glm::vec3 Transform::up()
{
	return glm::normalize(glm::cross(right(), front()));
}

glm::mat4 Transform::model()
{
	glm::mat4 model = glm::mat4(1.0f);

	model = glm::translate(model, position);
	
	model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.f, 0.f, 0.f));
	model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.f, 1.f, 0.f));
	model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.f, 0.f, 1.f));
	
	model = glm::scale(model, scale);
	
	return model;
}

glm::mat4 Transform::getTransformMatrix()
{
	// Start with rotation:
	glm::mat3 rot = glm::toMat4(orientation);
	
	// Break it up into columns:
	glm::vec4 c0(rot[0].x, rot[1].x, rot[2].x, 0);
	glm::vec4 c1(rot[0].y, rot[1].y, rot[2].y, 0);
	glm::vec4 c2(rot[0].z, rot[1].z, rot[2].z, 0);
	glm::vec4 c3(0, 0, 0, 1);

	// Apply scale:
	c0 *= scale.x;
	c1 *= scale.y;
	c2 *= scale.z;

	// Apply translation:
	c3[0] = position.x;
	c3[1] = position.y;
	c3[2] = position.z;

	// Compose and return result:
	return glm::mat4(c0, c1, c2, c3);
}

void Transform::updateChildren()
{
	glm::vec3 translation;
	glm::vec3 rotation;
	glm::vec3 scale;
	
	for (auto child : children)
	{
		child->position += translation;
		
	}
}

void Transform::onBeforeDraw()
{
	if (parent)
	{
		// parent * position
		position = transformToMat3(parent->getTransformMatrix()) * position;

		// orientation * parent
		glm::vec4 temp(orientation.x, orientation.y, orientation.z, orientation.w);
		temp = temp * parent->getTransformMatrix();
		glm::quat out(temp.w, temp.x, temp.y, temp.z);
		orientation = out;
		
		// scale
		// ...
	}

	//rotation = quatToEuler(orientation);
}

void Transform::drawEditor()
{

	
	ImGui::InputFloat3("position", glm::value_ptr(position));
	ImGui::InputFloat3("rotation", glm::value_ptr(rotation));
	ImGui::InputFloat4("orientation", glm::value_ptr(orientation));
	ImGui::InputFloat3("scale", glm::value_ptr(scale));
}

Transform::~Transform()
{
}

glm::mat3 Transform::transformToMat3(glm::mat4 t)
{
	glm::vec3 c0(t[0].x, t[1].x, t[2].x);
	glm::vec3 c1(t[0].y, t[1].y, t[2].y);
	glm::vec3 c2(t[0].z, t[1].z, t[2].z);
	
	return glm::mat3(c0, c1, c2);
}

glm::vec3 Transform::quatToEuler(glm::quat q)
{
	glm::vec3 angles;

	// roll (x-axis rotation)
	double sinr_cosp = 2 * (q.w * q.x + q.y * q.z);
	double cosr_cosp = 1 - 2 * (q.x * q.x + q.y * q.y);
	angles.z = std::atan2(sinr_cosp, cosr_cosp);

	// pitch (y-axis rotation)
	double sinp = 2 * (q.w * q.y - q.z * q.x);
	if (std::abs(sinp) >= 1)
		angles.y = std::copysign(PI / 2, sinp); // use 90 degrees if out of range
	else
		angles.y = std::asin(sinp);

	// yaw (z-axis rotation)
	double siny_cosp = 2 * (q.w * q.z + q.x * q.y);
	double cosy_cosp = 1 - 2 * (q.y * q.y + q.z * q.z);
	angles.x = std::atan2(siny_cosp, cosy_cosp);

	return angles;
}