#pragma once

#include "gpu/screen_fbo.h"

#include "pch.h"

class Viewport
{
public:
    void render(std::shared_ptr<ScreenFBO> & renderTarget);

private:
    Size size;
};