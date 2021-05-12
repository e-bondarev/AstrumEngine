#include "viewport.h"

#include "imgui/imgui.h"
#include "imgui/util.h"

#include "core/window/window.h"

Size Viewport::Render(std::shared_ptr<OpenGL::ScreenFBO> & renderTarget, std::shared_ptr<Scene> & scene)
{
    ImGui::Begin("Viewport");
        ImGuiWindowBoundaries boundaries = ImGuiUtil::Update();
        ImGui::Image((void*)(intptr_t)renderTarget->GetTextureHandle(), ImVec2(boundaries.Size.Width, boundaries.Size.Height), ImVec2(0, 0), ImVec2(1, -1));
    ImGui::End();

    if (A_MOUSE_BUTTON_RELEASED(MOUSE_BUTTON_LEFT))
    {
        Pos mouseCoordsWindowSpace = Window::GetMousePos();
        Pos viewportCoords = { mouseCoordsWindowSpace.x - boundaries.Pos.x, mouseCoordsWindowSpace.y - boundaries.Pos.y + 24 };

        renderTarget->Bind();
            std::array<unsigned char, 3> pixel = renderTarget->GetPixel<3>(GL_COLOR_ATTACHMENT1, viewportCoords);
        renderTarget->Unbind();

        unsigned int id = ColorToID({ pixel[0], pixel[1], pixel[2] });

        scene->SetSelectedObjectID(id);
    }

    return boundaries.Size;
}