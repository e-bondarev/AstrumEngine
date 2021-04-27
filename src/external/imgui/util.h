#pragma once

#include "imgui.h"

#include "pch.h"

struct ImGuiWindowBoundaries
{
    Pos pos;
    Size size;
};

namespace ImGuiUtil
{
    inline ImGuiWindowBoundaries& update()
    {
        static ImGuiWindowBoundaries boundaries;

        ImVec2 vMin = ImGui::GetWindowContentRegionMin();
        ImVec2 vMax = ImGui::GetWindowContentRegionMax();

        vMin.x += ImGui::GetWindowPos().x;
        vMin.y += ImGui::GetWindowPos().y;
        vMax.x += ImGui::GetWindowPos().x;
        vMax.y += ImGui::GetWindowPos().y;

        boundaries.pos.x = vMin.x;
        boundaries.pos.y = vMin.y;

        boundaries.size.width = vMax.x - vMin.x;
        boundaries.size.height = vMax.y - vMin.y;

        return boundaries;
    }
}