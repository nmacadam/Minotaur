#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <functional>
#include "Utilities/action.h"

class Debug
{
public:
	using f_void_t = void(*)(std::string);
	
	static void Log(std::string log)
	{
		std::cout << "This is a log!\n";
		onLog.invoke(log);
		//runCallback(log);
	}

	static void LogWarning(std::string log)
	{
		std::cout << "This is a warning!\n";
	}

	static void LogError(std::string log)
	{
		std::cout << "This is a error!\n";
	}

	static void Subscribe(std::function<void(std::string)> onLog)
	{
		actions.push_back(onLog);
	}

	static void Unsubscribe(f_void_t action)
	{
		//actions.
	}

	static Action<std::string> onLog;
	
private:
	static void runCallback(std::string log)
	{
		for (const auto& action : actions)
		{
			action(log);
		}
	}
	
	static std::vector<std::function<void(std::string)>> actions;
};
