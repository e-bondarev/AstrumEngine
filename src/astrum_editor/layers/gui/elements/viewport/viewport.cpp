#include "viewport.h"

#include "imgui/imgui.h"

#include "../../../graphics/graphics.h"

void Viewport::render(unsigned int fboTextureId)
{
    ImGui::Begin("Viewport");

    ImGui::Image((void*)(intptr_t)fboTextureId, ImVec2(800, 600), ImVec2(0, 0), ImVec2(1, -1));

    ImGui::End();
}