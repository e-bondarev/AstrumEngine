#pragma once

struct Size
{
    float width;
    float height;

    inline bool operator==(const Size& a) const
    {
        return width == a.width && height == a.height;
    }

    inline bool operator!=(const Size& a) const
    {
        return !((*this) == a);
    }
};

struct Pos
{
    float x;
    float y;

    inline bool operator==(const Pos& a) const
    {
        return x == a.x && y == a.y;
    }

    inline bool operator!=(const Pos& a) const
    {
        return !((*this) == a);
    }
};