#include "Hierarchy.h"
#include "../Engine.h"

#include "../../imgui/imgui.h"


void Hierarchy::render(Engine* engine)
{
	GameState* state = engine->peekState();

    //static void ShowExampleAppPropertyEditor(bool* p_open)
    {
        ImGui::SetNextWindowSize(ImVec2(430, 450), ImGuiCond_FirstUseEver);
        if (!ImGui::Begin("Hierarchy"/*, p_open*/))
        {
            ImGui::End();
            return;
        }

        //HelpMarker("This example shows how you may implement a property editor using two columns.\nAll objects/fields data are dummies here.\nRemember that in many simple cases, you can use ImGui::SameLine(xxx) to position\nyour cursor horizontally instead of using the Columns() API.");

        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(2, 2));
        ImGui::Columns(2);
        ImGui::Separator();

        struct funcs
        {
            // display entity and its components along with their respective editor fields
        	static void ShowEntity(Entity* entity, const char* prefix, int uid)
            {
                ImGui::PushID(uid);                      // Use object uid as identifier. Most commonly you could also use the object pointer as a base ID.
                ImGui::AlignTextToFramePadding();  // Text and Tree nodes are less high than regular widgets, here we add vertical spacing to make the tree lines equal high.
                bool node_open = ImGui::TreeNode("Object", "%s_%u", prefix, uid);
                ImGui::NextColumn();
                ImGui::AlignTextToFramePadding();
                ImGui::Text("some entity");
                ImGui::NextColumn();
                if (node_open)
                {
                    auto components = entity->getAllComponents();
                	for (int i = 0; i < components->size(); i++)
                	{
                		// Get component type name
                        std::string name = typeid(*(*components)[i]).name();
                		
                        ImGui::PushID(i); // Use field index as identifier.
                        // Here we use a TreeNode to highlight on hover (we could use e.g. Selectable as well)
                        ImGui::AlignTextToFramePadding();
                        ImGui::TreeNodeEx(name.c_str(), ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_Bullet, (name + " %d").c_str(), i);
                        ImGui::NextColumn();
                		
                        ImGui::SetNextItemWidth(-1);
                        (*components)[i]->drawEditor();
                        ImGui::NextColumn();
                        ImGui::PopID();
                	}
                    ImGui::TreePop();
                }
                ImGui::PopID();
            }
        };
    	
		// Iterate over entity pointers
		for (int i = 0; i < state->entities.count(); i++)
		{
            Entity* e = state->entities.getEntity(i);
            funcs::ShowEntity(e, e->name.c_str(), i);
		}

        ImGui::Columns(1);
        ImGui::Separator();
        ImGui::PopStyleVar();
        ImGui::End();
    }
}
