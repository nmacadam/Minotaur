#pragma once
#include <GL/glew.h>
#include <string>
#include <SDL.h>
const int FLIP_VERTICAL = 1;
const int FLIP_HORIZONTAL = 2;

class Texture
{
public:
	Texture(){}
	Texture(std::string path, GLenum type);
	~Texture();

	static Texture load(std::string path, GLenum type);
	
	inline GLuint getID() const { return id; }

	void bind(const GLint texture_unit);
	void unbind();

	GLuint id;
	GLint textureUnit;
	int width;
	int height;
	std::string path;
	
	unsigned int type;

protected:
	SDL_Surface* flip_vertical(SDL_Surface* sfc) {
		SDL_Surface* result = SDL_CreateRGBSurface(sfc->flags, sfc->w, sfc->h,
			sfc->format->BytesPerPixel * 8, sfc->format->Rmask, sfc->format->Gmask,
			sfc->format->Bmask, sfc->format->Amask);
		const auto pitch = sfc->pitch;
		const auto pxlength = pitch * (sfc->h - 1);
		auto pixels = static_cast<unsigned char*>(sfc->pixels) + pxlength;
		auto rpixels = static_cast<unsigned char*>(result->pixels);
		for (auto line = 0; line < sfc->h; ++line) {
			memcpy(rpixels, pixels, pitch);
			pixels -= pitch;
			rpixels += pitch;
		}
		return result;
	}
};

