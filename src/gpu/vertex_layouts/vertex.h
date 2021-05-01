#pragma once

#include "math/math.h"

#include "gpu/common/vertex_buffer_layout.h"

struct Vertex
{
    Vec3 Position;
    Vec2 UV;
    Vec3 Normal;

    inline static std::vector<VertexBufferLayout> GetLayout() {
        return {
            { 3, sizeof(Vertex), offsetof(Vertex, Position) },
            { 2, sizeof(Vertex), offsetof(Vertex, UV) },
            { 3, sizeof(Vertex), offsetof(Vertex, Normal) },
        };
    }
};