#pragma once

#include "gpu/backends/opengl/screen_fbo.h"

#include "pch.h"

class Viewport
{
public:
    Size Render(std::shared_ptr<OpenGL::ScreenFBO> & renderTarget);
};