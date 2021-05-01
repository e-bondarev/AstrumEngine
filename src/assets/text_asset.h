#pragma once

#include "asset.h"

struct TextAsset : public Asset
{
	std::string Content;

	void Load(const std::string& path) override;

	TextAsset(const std::string& path);
};