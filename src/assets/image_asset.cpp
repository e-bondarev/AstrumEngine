#include "image_asset.h"

//#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"

void ImageAsset::Load(const std::string& path)
{
	int width, height;
	Data = stbi_load((ASTRUM_ROOT + path).c_str(), &width, &height, &Channels, 0);
	Size = { static_cast<float>(width), static_cast<float>(height) };
}

ImageAsset::ImageAsset(const std::string& path)
{
	Load(path);
}

ImageAsset::~ImageAsset()
{
	stbi_image_free(Data);
}