#pragma once

struct Size
{
    float Width;
    float Height;

    inline bool operator==(const Size& a) const
    {
        return Width == a.Width && Height == a.Height;
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