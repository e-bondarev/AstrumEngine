#pragma once

#include <memory>

class GUI;
class Graphics;

struct Layers
{
    std::shared_ptr<GUI> gui;
    std::shared_ptr<Graphics> graphics;
};