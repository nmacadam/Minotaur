#include "Texture.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

Texture::Texture(std::string path, GLenum type)
{
	this->path = path;
	
	// Load image into SDL surface
	SDL_Surface* temp = nullptr;
	temp = IMG_Load(path.c_str());
	if (!temp)
	{
		std::cerr << "Unable to load image " << path << "! SDL_image Error: " << IMG_GetError() << "\n";
		return;
	}

	temp = flip_vertical(temp);

	// Generate GL texture and bind
	glGenTextures(1, &id);
	glBindTexture(type, id);

	// Select color mode
	int mode = GL_RGB;
	if (temp->format->BytesPerPixel == 4) mode = GL_RGBA;

	//set texture's parameters
	glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	//glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); //pixel filtering (TURN OFF LATER!)

	//send off texture elements
	glTexImage2D(type, 0, mode, temp->w, temp->h, 0, mode, GL_UNSIGNED_BYTE, temp->pixels);

	//generate mipmap for texture
	glGenerateMipmap(type);

	width = temp->w;
	height = temp->h;

	//this->textureUnit = texture_unit;
	this->type = type;

	// Unbind and delete temporary surface
	glActiveTexture(0);
	glBindTexture(type, 0);
	SDL_FreeSurface(temp);

	std::cout << "Loaded texture successfully\n";
}

Texture::~Texture()
{
	glDeleteTextures(1, &id);
}

Texture Texture::load(std::string path, GLenum type)
{
	Texture texture;
	
	// Load image into SDL surface
	SDL_Surface* temp = nullptr;
	temp = IMG_Load(path.c_str());
	if (!temp)
	{
		std::cerr << "Unable to load image " << path << "! SDL_image Error: " << IMG_GetError() << "\n";
		return texture;
	}

	// Generate GL texture and bind
	glGenTextures(1, &texture.id);
	glBindTexture(type, texture.id);

	// Select color mode
	int mode = GL_RGB;
	if (temp->format->BytesPerPixel == 4) mode = GL_RGBA;

	//set texture's parameters
	glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //pixel filtering (TURN OFF LATER!)
	glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); //pixel filtering (TURN OFF LATER!)

	//send off texture elements
	glTexImage2D(type, 0, mode, temp->w, temp->h, 0, mode, GL_UNSIGNED_BYTE, temp->pixels);

	//generate mipmap for texture
	glGenerateMipmap(type);

	texture.width = temp->w;
	texture.height = temp->h;

	//texture.textureUnit = texture_unit;
	texture.type = type;

	// Unbind and delete temporary surface
	glActiveTexture(0);
	glBindTexture(type, 0);
	SDL_FreeSurface(temp);

	//std::cout << "Loaded texture successfully\n";
	return texture;
}

void Texture::bind(const GLint texture_unit)
{
	glActiveTexture(GL_TEXTURE0 + texture_unit);
	glBindTexture(type, id);
}

void Texture::unbind()
{
	glActiveTexture(0);
	glBindTexture(type, 0);
}