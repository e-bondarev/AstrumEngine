#pragma once

#include "pch.h"

#include <GL/glew.h>

class Shader
{
public:
    using str_list_t = std::vector<std::string>;
    Shader(const std::string& vs_code, const std::string& fs_code, const str_list_t& uniforms = {}, const str_list_t& inputs = {});

    void Bind();
    void Unbind();
    void Release();

    void CreateUniform(const std::string& name);
    void SetFloat(const std::string& name, const float value);
    void SetInt(const std::string& name, const int value);
    void SetVec3(const std::string& name, const GLfloat* vec);
    void SetVec4(const std::string& name, const GLfloat* vec);
    void SetMat4x4(const std::string& name, const GLfloat* matrix);
    void SetListMat4x4(const std::string& name, const GLfloat* list, const unsigned int size);
    void SetVec4(const float x, const float y, const float z);
    
    ~Shader();
    
private:
    std::map<std::string, unsigned int> locations;
    unsigned int location;

    unsigned int vsHandle;
    unsigned int fsHandle;

    void Link() const;
    unsigned int CreateShader(const std::string& shaderCode, const unsigned int& shaderType);

    unsigned int handle { 0 };

};