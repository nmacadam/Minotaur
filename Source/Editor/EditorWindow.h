#pragma once
class Engine;

class EditorWindow
{
public:
	virtual void render(Engine* engine) = 0;
};
