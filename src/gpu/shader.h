#pragma once

#include "pch.h"

class Shader
{
public:
    using str_list_t = std::vector<std::string>;
    Shader(const std::string& vs_code, const std::string& fs_code, const str_list_t& uniforms = {}, const str_list_t& inputs = {});    
    ~Shader();

    void bind();
    void unbind();

    void createUniform(const std::string& name);
    void setFloat(const std::string& name, float value);
    void setInt(const std::string& name, int value);
    void setVec3(const std::string& name, float const* const vec);
    void setVec4(const std::string& name, float const* const vec);
    void setMat4x4(const std::string& name, float const* const matrix);
    void setListMat4x4(const std::string& name, float const* const list, unsigned int size);
    
private:
    unsigned int handle { 0 };

    unsigned int vsHandle { 0 };
    unsigned int fsHandle { 0 };

    std::map<std::string, unsigned int> uniformLocations;

    void link() const;
    unsigned int createShader(const std::string& shaderCode, const unsigned int& shaderType);

    Shader(const Shader&) = delete;
    Shader& operator=(const Shader&) = delete;
};