#pragma once

#include "math/math.h"

inline static Vec3 IDToColor(unsigned int id)
{
	unsigned int red   = (id & 0x00ff0000) >> 16;
	unsigned int green = (id & 0x0000ff00) >> 8;
	unsigned int blue  = (id & 0x000000ff);

	return { red / 255.0f, green / 255.0f, blue / 255.0f };
}

inline static unsigned int ColorToID(Vec3 color)
{
	unsigned int rgb = color.x;
	rgb = (rgb << 8) + color.y;
	rgb = (rgb << 8) + color.z;

	return rgb;
}