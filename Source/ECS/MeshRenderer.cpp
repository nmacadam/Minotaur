#include "MeshRenderer.h"
#include <glm/glm.hpp>

//MeshRenderer::MeshRenderer(Mesh* mesh, Shader* shader): mesh(mesh), shader(shader)
//{
//}

MeshRenderer::MeshRenderer(Mesh* mesh, Material* material) : mesh(mesh), material(material)
{
}

void MeshRenderer::initialize()
{
	if (!entity->hasComponent<Transform>()) entity->addComponent<Transform>();
	transform = &entity->getComponent<Transform>();
}

void MeshRenderer::update()
{
}

void MeshRenderer::draw()
{
	material->shader->setMat4fv("model", transform->getTransformMatrix());
	material->use();
	material->shader->use();
	mesh->render(material->shader);
	//material->unuse();
	//material->shader->unuse();
}

MeshRenderer::~MeshRenderer()
{
}
