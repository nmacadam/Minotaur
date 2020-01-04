#pragma once
#include "TextureCache.h"
#include <SDL_ttf.h>
#include "Model.h"
#include <SDL_mixer.h>
#include "FontCache.h"
#include "ModelCache.h"

class ResourceManager
{
public:
	TextureCache Textures;
	FontCache Fonts;
	ModelCache Models;

private:
	std::map<std::string, Texture> textures;
	std::map<std::string, Model> models;
	std::map<std::string, Shader> shaders;

	/*std::map<std::string, TTF_Font> fonts;
	std::map<std::string, Mix_Chunk> sfx;
	std::map<std::string, Mix_Music> music;*/
};

