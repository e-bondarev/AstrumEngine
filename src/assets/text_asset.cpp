#include "text_asset.h"

#include <fstream>

void TextAsset::Load(const std::string& path)
{
    std::ifstream file;

    file.open(ASTRUM_ROOT + path);

    while (!file.eof())
    {
        std::string line;

        getline(file, line);

        Content.append(line.empty() ? "\n" : line);
    }

    file.close();
}

TextAsset::TextAsset(const std::string& path)
{
    Load(path);
}