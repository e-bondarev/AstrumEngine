#include "viewport.h"

#include "imgui/imgui.h"
#include "imgui/util.h"

Size Viewport::Render(std::shared_ptr<OpenGL::ScreenFBO> & renderTarget)
{
    ImGui::Begin("Viewport");
        ImGuiWindowBoundaries boundaries = ImGuiUtil::Update();
        ImGui::Image((void*)(intptr_t)renderTarget->GetTextureHandle(), ImVec2(boundaries.Size.Width, boundaries.Size.Height), ImVec2(0, 0), ImVec2(1, -1));
    ImGui::End();

    return boundaries.Size;
}