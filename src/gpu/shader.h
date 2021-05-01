#pragma once

#include "pch.h"

class Shader
{
public:
    using str_list_t = std::vector<std::string>;

    Shader(const std::string& vsCode, const std::string& fsCode, const str_list_t& uniforms = {});    
    ~Shader();

    void Bind() const;
    void Unbind() const;

    void CreateUniform(const std::string& name);
    void SetFloat(const std::string& name, float value);
    void SetInt(const std::string& name, int value);
    void SetVec3(const std::string& name, float const* const vec);
    void SetVec4(const std::string& name, float const* const vec);
    void SetMat4x4(const std::string& name, float const* const matrix);
    void SetListMat4x4(const std::string& name, float const* const list, unsigned int size);
    
private:
    unsigned int handle { 0 };

    unsigned int vsHandle { 0 };
    unsigned int fsHandle { 0 };

    std::map<std::string, unsigned int> uniformLocations;

    void Link() const;
    unsigned int CreateShader(const std::string& shaderCode, unsigned int shaderType);

    Shader(const Shader&) = delete;
    Shader& operator=(const Shader&) = delete;
};