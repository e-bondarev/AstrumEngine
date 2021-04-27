#include "dockspace.h"

#include "imgui/imgui.h"

void Dockspace::render()
{
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
	
	ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(viewport->Pos);
	ImGui::SetNextWindowSize(viewport->Size);
	ImGui::SetNextWindowViewport(viewport->ID);
	window_flags |= 
					ImGuiWindowFlags_NoTitleBar 
					| ImGuiWindowFlags_NoCollapse 
					| ImGuiWindowFlags_NoResize 
					| ImGuiWindowFlags_NoMove;
					
	window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

	static bool leave_open = true;
	ImGui::Begin("ENGINE_FULL_NAME", &leave_open, ImGuiWindowFlags_NoTitleBar);
	static int dockspace_id = ImGui::GetID("HUB_DockSpace");
	ImGui::DockSpace(dockspace_id , ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_None | ImGuiDockNodeFlags_PassthruCentralNode/*|ImGuiDockNodeFlags_NoResize*/);
	ImGui::End();
}