#pragma once
#include "Cache.h"
#include <ft2build.h>
#include "Font.h"

//class GlyphMap
//{
//
//private:
//	std::map<GLchar, Glyph> glyphs;
//};

class FontCache :
	public Cache<Font>
{
public:
	Font* Load(std::string path) override;
	Font* Load(std::string path, int fontSize);

private:
	
	const int defaultFontSize = 12;
};