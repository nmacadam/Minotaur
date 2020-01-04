#pragma once
#include "Cache.h"
#include "Model.h"

class ModelCache : Cache<Model>
{
public:
	Model* Load(std::string path) override;
};
