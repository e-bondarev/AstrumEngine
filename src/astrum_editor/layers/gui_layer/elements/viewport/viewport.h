#pragma once

#include "gpu/backends/opengl/screen_fbo.h"
#include "scene/scene.h"

class Viewport
{
public:
    Size Render(std::shared_ptr<OpenGL::ScreenFBO> & renderTarget, std::shared_ptr<Scene> & scene);
};