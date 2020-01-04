#include "GameWindow.h"
#include "../../External Libraries/imgui/imgui.h"
#include "../Engine.h"

void GameWindow::render(Engine* engine)
{
    ImGui::Begin("Game");

    //diffuseMap = new Texture("./container.png", 3, GL_TEXTURE_2D);
    //ImGui::Image((void*)(intptr_t)Engine::framebuffer, ImVec2(400, 400));
	
    ImGui::End();
}
