#include "Debug.h"

Action<std::string> Debug::onLog;

std::vector<std::function<void(std::string)>> Debug::actions;