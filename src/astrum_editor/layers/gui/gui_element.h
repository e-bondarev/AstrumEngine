#pragma once

class GUIElement
{
public:
    virtual void render() = 0;

    virtual ~GUIElement() {}
};