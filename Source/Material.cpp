#include "Material.h"

Material::Material(Shader* shader) : shader(shader)
{
}

Material::Material(Texture* diffuseMap, Texture* specularMap, Shader* shader): diffuseMap(diffuseMap),
                                                                               specularMap(specularMap), shader(shader)
{
}

void Material::use()
{
	if (diffuseMap)
	{
		shader->setInt("material.diffuse", 0);
		diffuseMap->bind(0);
	}
	if (specularMap)
	{
		shader->setInt("material.specular", 1);
		specularMap->bind(1);
	}
}

void Material::unuse()
{
	if (diffuseMap)
	{
		diffuseMap->unbind();
	}
	if (specularMap)
	{
		specularMap->unbind();
	}
}
