#include "ModelCache.h"

Model* ModelCache::Load(std::string path)
{
	//lookup texture
	auto mapItr = values.find(path);

	//if it doesn't exist already, add texture
	if (mapItr == values.end())
	{
		Model model(path);
		values.emplace(path, model);
		std::cout << "Loaded texture" << std::endl;

		// this seems wrong, but i can't figure out how to grab the pointer out of emplace
		return &model;
	}
	else
	{
		std::cout << "Obtained texture from cache" << std::endl;
		return &mapItr->second;
	}
}