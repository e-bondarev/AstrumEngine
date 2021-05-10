#include "viewport.h"

#include "imgui/imgui.h"
#include "imgui/util.h"

#include "core/window/window.h"

Size Viewport::Render(std::shared_ptr<OpenGL::ScreenFBO> & renderTarget, Pos** POS)
{
    ImGui::Begin("Viewport");
        ImGuiWindowBoundaries boundaries = ImGuiUtil::Update();
        ImGui::Image((void*)(intptr_t)renderTarget->GetTextureHandle(), ImVec2(boundaries.Size.Width, boundaries.Size.Height), ImVec2(0, 0), ImVec2(1, -1));
    ImGui::End();

    if (glfwGetMouseButton(Window::GetGlfwWindow(), GLFW_MOUSE_BUTTON_1))
    {
        double x, y;
        glfwGetCursorPos(Window::GetGlfwWindow(), &x, &y);

        Pos viewportCoords = { x - boundaries.Pos.x, y - boundaries.Pos.y + 24 };
        //Pos viewportCoords = { x - boundaries.Pos.x, y - boundaries.Pos.y };
        *POS = new Pos({ viewportCoords.x, viewportCoords.y });
    }

    return boundaries.Size;
}