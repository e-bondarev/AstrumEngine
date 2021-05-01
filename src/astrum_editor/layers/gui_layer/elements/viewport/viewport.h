#pragma once

#include "gpu/screen_fbo.h"

#include "pch.h"

class Viewport
{
public:
    void Render(std::shared_ptr<ScreenFBO> & renderTarget);

private:
    Size m_Size;
};