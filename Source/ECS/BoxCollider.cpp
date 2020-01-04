#include "BoxCollider.h"

BoxCollider::BoxCollider(glm::vec3 bounds)
{	
	/*if (!entity->hasComponent<Transform>()) entity->addComponent<Transform>();
	transform = &entity->getComponent<Transform>();*/

	this->bounds = bounds;
	//center = transform->position;
}

BoxCollider::BoxCollider(glm::vec3 bounds, glm::vec3 center)
{
	/*if (!entity->hasComponent<Transform>()) entity->addComponent<Transform>();
	transform = &entity->getComponent<Transform>();*/

	this->bounds = bounds;
	this->center = center;
}

BoxCollider::BoxCollider(glm::vec3 bounds, glm::vec3 center, bool isStatic)
{
	this->bounds = bounds;
	this->center = center;
	this->isStatic = isStatic;
}

void BoxCollider::initialize()
{	
	if (!entity->hasComponent<Transform>()) entity->addComponent<Transform>();
	transform = &entity->getComponent<Transform>();
}

void BoxCollider::update()
{
}

void BoxCollider::drawEditor()
{
}

//bool BoxCollider::detectCollision(Collider* other)
//{
//	auto a = center + transform->position;
//
//	const std::type_info& type_info = typeid(*other);
//	if (type_info == typeid(BoxCollider))
//	{
//		auto b_collider = static_cast<BoxCollider*>(other);
//		
//		auto b = b_collider->center + b_collider->transform->position;
//
//		// AABB
//		return	(a.x - bounds.x <= b.x + b_collider->bounds.x && a.x + bounds.x >= b.x - b_collider->bounds.x) &&
//				(a.y - bounds.y <= b.y + b_collider->bounds.y && a.y + bounds.y >= b.y - b_collider->bounds.y) &&
//				(a.z - bounds.z <= b.z + b_collider->bounds.z && a.z + bounds.z >= b.z - b_collider->bounds.z);
//	}
//
//	return false;
//}



BoxCollider::~BoxCollider()
{
}

bool BoxCollider::pointInAABB(glm::vec3 point, BoxCollider* box)
{
	auto boxPos = box->center + box->transform->position;
	
	return	(point.x >= boxPos.x - box->bounds.x && point.x <= boxPos.x + box->bounds.x) &&
			(point.y >= boxPos.y - box->bounds.y && point.y <= boxPos.y + box->bounds.y) &&
			(point.z >= boxPos.z - box->bounds.z && point.z <= boxPos.z + box->bounds.z);
}

bool BoxCollider::AABBIntersection(BoxCollider* a, BoxCollider* b)
{
	auto aPos = a->center + a->transform->position;
	auto bPos = b->center + b->transform->position;

	return	(aPos.x - a->bounds.x <= bPos.x + b->bounds.x && aPos.x + a->bounds.x >= bPos.x - b->bounds.x) &&
			(aPos.y - a->bounds.y <= bPos.y + b->bounds.y && aPos.y + a->bounds.y >= bPos.y - b->bounds.y) &&
			(aPos.z - a->bounds.z <= bPos.z + b->bounds.z && aPos.z + a->bounds.z >= bPos.z - b->bounds.z);
}