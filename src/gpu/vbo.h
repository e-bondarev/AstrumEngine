#pragma once

#include "pch.h"

class VBO
{
public:
    VBO(unsigned int type);
    ~VBO();

    void storeData(const std::vector<float>& data);
    void storeData(const std::vector<int>& data);
    void storeData(const std::vector<unsigned int>& data);

    void bind();
    void unbind();
    void release();

    unsigned int getHandle() const;

private:
    unsigned int handle;
    unsigned int type;

    VBO(const VBO&) = delete;
    VBO& operator=(const VBO&) = delete;
};