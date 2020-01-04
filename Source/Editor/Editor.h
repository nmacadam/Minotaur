#pragma once
#include "../Engine.h"
#include "FileBrowser.h"
#include "Toolbar.h"
#include "GameWindow.h"
#include "Hierarchy.h"
#include "Console.h"

#include "../../External Libraries/imgui/imgui.h"

#include <vector>

class Editor
{
public:
	Editor(Engine* engine);
	~Editor();

	bool initialize();

	void processEvents();
	void update();
	void render();

	void clean();

	Toolbar	toolbar;
	FileBrowser browser;
	GameWindow gameWindow;
	Hierarchy hierarchy;
	Console console;
	
private:
	std::vector<EditorWindow*> editorWindows;
	
	Engine* engine;
	ImGuiIO* io;
};
