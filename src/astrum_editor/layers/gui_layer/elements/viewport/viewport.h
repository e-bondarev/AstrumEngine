#pragma once

#include "gpu/backends/opengl/screen_fbo.h"

class Viewport
{
public:
    Size Render(std::shared_ptr<OpenGL::ScreenFBO> & renderTarget);
};