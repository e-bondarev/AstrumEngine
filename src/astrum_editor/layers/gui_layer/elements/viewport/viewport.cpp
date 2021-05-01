#include "viewport.h"

#include "imgui/imgui.h"
#include "imgui/util.h"

void Viewport::Render(std::shared_ptr<ScreenFBO> & renderTarget)
{
    ImGui::Begin("Viewport");

    ImGuiWindowBoundaries boundaries = ImGuiUtil::update();

    if (boundaries.size != m_Size)
    {
        m_Size = boundaries.size;
        renderTarget->resize(m_Size.Width, m_Size.Height);
        glViewport(0, 0, m_Size.Width, m_Size.Height);
    }

    ImGui::Image((void*)(intptr_t)renderTarget->getTextureHandle(), ImVec2(m_Size.Width, m_Size.Height), ImVec2(0, 0), ImVec2(1, -1));

    ImGui::End();
}