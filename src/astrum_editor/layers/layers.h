#pragma once

class GUILayer;
class GraphicsLayer;
class SceneLayer;

struct Layers
{
    std::shared_ptr<GUILayer> m_GUI;
    std::shared_ptr<GraphicsLayer> m_Graphics;
    std::shared_ptr<SceneLayer> m_Scene;
};