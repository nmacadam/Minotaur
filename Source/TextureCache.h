#pragma once
#include <GL/glew.h>
#include <string>
#include <map>
#include "Cache.h"
#include "Texture.h"

class TextureCache : Cache<Texture>
{
public:
	TextureCache();
	~TextureCache();

	Texture* Load(std::string path) override;
	Texture* Load(std::string path, GLenum type = GL_TEXTURE_2D);
	void Add(Texture texture);
	void Unload(std::string path) override;
	void ClearCache() override;
};

