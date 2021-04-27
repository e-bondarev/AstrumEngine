#pragma once

#include "pch.h"

#include <GL/glew.h>

class Shader
{
public:
    using str_list_t = std::vector<std::string>;
    Shader(const std::string& vs_code, const std::string& fs_code, const str_list_t& uniforms = {}, const str_list_t& inputs = {});

    void bind();
    void unbind();
    void release();

    void createUniform(const std::string& name);
    void setFloat(const std::string& name, const float value);
    void setInt(const std::string& name, const int value);
    void setVec3(const std::string& name, const GLfloat* vec);
    void setVec4(const std::string& name, const GLfloat* vec);
    void setMat4x4(const std::string& name, const GLfloat* matrix);
    void setListMat4x4(const std::string& name, const GLfloat* list, const unsigned int size);
    void setVec4(const float x, const float y, const float z);
    
    ~Shader();
    
private:
    std::map<std::string, unsigned int> locations;
    unsigned int location;

    unsigned int vsHandle;
    unsigned int fsHandle;

    void link() const;
    unsigned int createShader(const std::string& shaderCode, const unsigned int& shaderType);

    unsigned int handle { 0 };

};