#pragma once

#include "imgui.h"

#include "pch.h"

struct ImGuiWindowBoundaries
{
    Pos Pos;
    Size Size;
};

namespace ImGuiUtil
{
    inline ImGuiWindowBoundaries& Update()
    {
        static ImGuiWindowBoundaries boundaries;

        ImVec2 vMin = ImGui::GetWindowContentRegionMin();
        ImVec2 vMax = ImGui::GetWindowContentRegionMax();

        vMin.x += ImGui::GetWindowPos().x;
        vMin.y += ImGui::GetWindowPos().y;
        vMax.x += ImGui::GetWindowPos().x;
        vMax.y += ImGui::GetWindowPos().y;

        boundaries.Pos.x = vMin.x;
        boundaries.Pos.y = vMin.y;

        boundaries.Size.Width = vMax.x - vMin.x;
        boundaries.Size.Height = vMax.y - vMin.y;

        return boundaries;
    }
}