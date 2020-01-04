#include "FontCache.h"
#include <iostream>

Font* FontCache::Load(std::string path)
{
	return Load(path, defaultFontSize);
}

// UNTESTED!
Font* FontCache::Load(std::string path, int fontSize)
{
	//lookup texture
	auto mapItr = values.find(path);

	//if it doesn't exist already, add texture
	if (mapItr == values.end())
	{
		auto empResult = values.emplace(path, Font(path));
		std::cout << "Loaded font" << std::endl;

		// return newly emplaced font
		return &empResult.first->second;
	}
	else
	{
		std::cout << "Obtained font from cache" << std::endl;
		return &mapItr->second;
	}
}