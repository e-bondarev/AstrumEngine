#pragma once

#include "asset.h"

struct ImageAsset : public Asset
{
	Size Size;
	int Channels;
	unsigned char* Data;

	void Load(const std::string& path) override;

	ImageAsset(const std::string& path);
	~ImageAsset();
};