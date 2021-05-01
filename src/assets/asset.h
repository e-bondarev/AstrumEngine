#pragma once

#include "pch.h"

#include "gpu/vertex_layouts/vertex.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <glm/glm.hpp>

#define ASTRUM_ROOT "D:/Dev/AstrumEngine/"

struct Asset
{
    virtual void Load(const std::string& path) = 0;
};