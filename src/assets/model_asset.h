#pragma once

#include "asset.h"

struct ModelAsset : public Asset
{
    std::vector<Vertex> Vertices;
    std::vector<int> Indices;

    void Load(const std::string& path) override;

    ModelAsset(const std::string& path);
    ModelAsset() = default;
};