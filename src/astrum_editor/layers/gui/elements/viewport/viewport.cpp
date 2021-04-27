#include "viewport.h"

#include "imgui/imgui.h"
#include "imgui/util.h"

void Viewport::render(std::shared_ptr<ScreenFBO> & renderTarget)
{
    ImGui::Begin("Viewport");

    ImGuiWindowBoundaries boundaries = ImGuiUtil::update();

    if (boundaries.size != size)
    {
        size = boundaries.size;
        renderTarget->resize(size.width, size.height);
        glViewport(0, 0, size.width, size.height);
    }

    ImGui::Image((void*)(intptr_t)renderTarget->getTextureHandle(), ImVec2(size.width, size.height), ImVec2(0, 0), ImVec2(1, -1));

    ImGui::End();
}