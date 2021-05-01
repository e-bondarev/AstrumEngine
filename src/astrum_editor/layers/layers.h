#pragma once

class GUILayer;
class GraphicsLayer;

struct Layers
{
    std::shared_ptr<GUILayer> GUI;
    std::shared_ptr<GraphicsLayer> Graphics;
};