#pragma once
#include <string>
#include <map>

#include <GL/glew.h>
#include <ft2build.h>
#include <freetype/freetype.h>

#include "Glyph.h"

#include "Shader.h"

class Font
{
public:
	Font(std::string path/*, int size*/);

	//void RenderText(Shader* s, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);

	Glyph getGlyph(GLchar character) { return glyphs[character]; }

	std::string path;
private:
	void buildGlyphTextures();

	int fontSize;
	std::map<GLchar, Glyph> glyphs;

	//GLuint VAO, VBO;

	FT_Library ft;
	FT_Face face;
};
