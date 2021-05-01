#pragma once

#define ASTRUM_ROOT "D:/Dev/AstrumEngine/"

struct Asset
{
    virtual void Load(const std::string& path) = 0;
};