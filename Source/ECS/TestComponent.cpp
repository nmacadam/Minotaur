#include "TestComponent.h"
#include "../../External Libraries/imgui/imgui.h"
#include "../MTime.h"

void TestComponent::initialize()
{
	if (!entity->hasComponent<Transform>()) entity->addComponent<Transform>();
	transform = &entity->getComponent<Transform>();
	//std::cout << "component init\n";
}

void TestComponent::update()
{
	transform->rotation.y += 5.f * MTime::deltaTime;
	transform->updateChildren();
	//std::cout << "component update\n";
}

void TestComponent::draw()
{
	//std::cout << "component draw\n";
}

void TestComponent::drawEditor()
{
	static float vec4a[4] = { 0.10f, 0.20f, 0.30f, 0.44f };
	ImGui::InputFloat3("yooo float3", vec4a);
}

TestComponent::~TestComponent()
{
	std::cout << "component destroyed\n";
}
