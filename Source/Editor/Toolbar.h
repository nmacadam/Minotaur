#pragma once
#include "EditorWindow.h"
class Toolbar :
	public EditorWindow
{
public:
	void render(Engine* engine) override;
	void showFileMenu();
	void showRendererMenu();
};