#pragma once
#include "Collider.h"
#include <glm/vec3.hpp>
#include "Transform.h"

class BoxCollider : public Collider<BoxCollider>
{
public:
	BoxCollider(glm::vec3 bounds);
	BoxCollider(glm::vec3 bounds, glm::vec3 center);
	BoxCollider(glm::vec3 bounds, glm::vec3 center, bool isStatic);
	
	void initialize() override;
	void update() override;
	void drawEditor() override;
	//bool detectCollision(Collider* other) override;
	~BoxCollider() override;

	//void implementation() {}

	Transform* transform;

	glm::vec3 bounds;
	glm::vec3 center;

	bool isStatic = false;
	
private:

	bool pointInAABB(glm::vec3 point, BoxCollider* box);
	bool AABBIntersection(BoxCollider* a, BoxCollider* b);
	
};
