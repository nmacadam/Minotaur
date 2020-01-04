#pragma once
#include "Texture.h"
#include "Shader.h"

#include <cereal/cereal.hpp>

class Material
{
public:
	Material() {}
	Material(Shader* shader);
	Material(Texture* diffuseMap, Texture* specularMap, Shader* shader);

	void use();
	void unuse();

	Texture* diffuseMap = nullptr;
	Texture* specularMap = nullptr;
	Shader* shader;

	/*template<class Archive>
	void save(Archive& archive) const
	{
		archive(CEREAL_NVP(diffuseMap->path), CEREAL_NVP(specularMap->path));
	}

	template<class Archive>
	void load(Archive& archive)
	{
		std::string diffusePath;
		std::string specularPath;
		
		archive(diffusePath, specularPath);

		std::cout << diffusePath << std::endl;
		std::cout << specularPath << std::endl;
	}*/
};
