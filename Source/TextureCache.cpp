#include "TextureCache.h"
#include <iostream>

TextureCache::TextureCache()
= default;

TextureCache::~TextureCache()
{
	ClearCache();
}

Texture* TextureCache::Load(std::string path)
{
	return Load(path, GL_TEXTURE_2D);
}

Texture* TextureCache::Load(std::string path, GLenum type)
{
	//lookup texture
	auto mapItr = values.find(path);

	//if it doesn't exist already, add texture
	if (mapItr == values.end())
	{
		Texture* texture = new Texture(path, type);
		
		//Texture newTexture(path, type);
		auto empResult = values.emplace(path, *texture);
		std::cout << "Loaded texture" << std::endl;
		
		return &empResult.first->second;
	}
	else
	{
		std::cout << "Obtained texture from cache" << std::endl;
		return &mapItr->second;
	}
}

void TextureCache::Add(Texture texture)
{
	values.emplace(texture.path, texture);
}

void TextureCache::Unload(std::string path)
{
	//lookup texture
	auto mapItr = values.find(path);
	//if it doesn't exist, return
	if (mapItr == values.end()) return;
	else
	{
		delete &mapItr->second;
		values.erase(mapItr);
	}
}

void TextureCache::ClearCache()
{
	//for (auto itr = values.begin(); itr != values.end(); ++itr)
	//{
	//	delete &itr->second;
	//}
	//
	///*for (auto value : values)
	//{
	//	delete &value.second;
	//}*/
	values.clear();
}