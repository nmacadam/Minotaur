#pragma once
#include "ECS.h"
#include "../Mesh.h"
#include "../Material.h"
#include <cereal/cereal.hpp>
#include "Transform.h"

class MeshRenderer : public Component
{
public:
	MeshRenderer() {}
	//MeshRenderer(Mesh* mesh, Shader* shader);
	MeshRenderer(Mesh* mesh, Material* material);

	void initialize() override;
	void update() override;
	void draw() override;
	~MeshRenderer() override;
	
	Transform* transform;
	Mesh* mesh;
	//Shader* shader;
	Material* material;

	template <class Archive>
	void serialize(Archive& ar)
	{
		ar(cereal::base_class<Component>(this));
	}
};

CEREAL_REGISTER_TYPE(MeshRenderer);