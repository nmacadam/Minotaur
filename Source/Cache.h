#pragma once
#include <string>
#include <map>
// bleh
template <typename T> class Cache
{
public:
	Cache() {}
	virtual ~Cache() = default;
	virtual T* Load(std::string path) = 0;
	virtual void Unload(std::string path)
	{
		//lookup texture
		auto mapItr = values.find(path);
		//if it doesn't exist, return
		if (mapItr == values.end()) return;
		else
		{
			values.erase(mapItr);
		}
	}
	virtual void ClearCache()
	{
		values.clear();
	}

protected:
	std::map<std::string, T> values;
};
