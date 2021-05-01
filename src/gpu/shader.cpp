#include "shader.h"

#include <GL/glew.h>

Shader::Shader(
    const std::string &vsCode,
    const std::string &fsCode,
    const str_list_t& uniformVariables
)
{
    handle = glCreateProgram();

    vsHandle = createShader(vsCode, GL_VERTEX_SHADER);
    fsHandle = createShader(fsCode, GL_FRAGMENT_SHADER);

    link();

    for (int i = 0; i < uniformVariables.size(); i++)
    {
        createUniform(uniformVariables[i]);
    }

    A_DEBUG_LOG_OUT("[Call] Shader constructor");
}

Shader::~Shader()
{
    Unbind();
    glDetachShader(handle, vsHandle);
    glDetachShader(handle, fsHandle);
    glDeleteShader(vsHandle);
    glDeleteShader(fsHandle);
    glDeleteProgram(handle);

    A_DEBUG_LOG_OUT("[Call] Shader destructor");
}

void Shader::link() const
{
    glLinkProgram(handle);

    if (vsHandle != 0)
    {
        glDetachShader(handle, vsHandle);
    }

    if (fsHandle != 0)
    {
        glDetachShader(handle, fsHandle);
    }

    glValidateProgram(handle);
}

unsigned int Shader::createShader(const std::string &shaderCode, unsigned int shaderType)
{
    const unsigned int shaderID = glCreateShader(shaderType);

    const char *c_str = shaderCode.c_str();

    glShaderSource(shaderID, 1, &c_str, NULL);
    glCompileShader(shaderID);

    int status;

    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &status);

    if (status == GL_FALSE)
    {
        int length;
        glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &length);
        std::vector<char> log(length);
        glGetShaderInfoLog(shaderID, length, &length, &log[0]);
        A_LOG_OUT("[File: astrum_gpu/shader.cpp, Function: create_shader()]: Error occured while compiling a shader: " << &log[0]);
        return -1;
    }

    glAttachShader(handle, shaderID);

    return shaderID;
}

void Shader::Bind()
{
    glUseProgram(handle);
}

void Shader::Unbind()
{
    glUseProgram(0);
}

void Shader::createUniform(const std::string &name)
{
    int location = glGetUniformLocation(handle, name.c_str());

    uniformLocations.insert(
        std::pair<std::string, int>(
            name.c_str(), 
            location
        )
    );
}

void Shader::setFloat(const std::string &name, float value)
{
#ifdef A_SHADER_DEBUG
    if (locations.find(name) == locations.end())
    {
        A_LOG_OUT("[DEBUG, File: astrum_gpu/shader.h, Function: setMat4x4()]: Variable " << name << " doesn't exist.");
        return;
    }
#endif

    glUniform1f(uniformLocations.at(name), value);
}

void Shader::setInt(const std::string &name, int value)
{
#ifdef A_SHADER_DEBUG
    if (locations.find(name) == locations.end())
    {
        A_LOG_OUT("[DEBUG, File: astrum_gpu/shader.h, Function: setMat4x4()]: Variable " << name << " doesn't exist.");
        return;
    }
#endif

    glUniform1i(uniformLocations.at(name), value);
}

void Shader::SetMat4x4(const std::string &name, float const* const matrix)
{
#ifdef A_SHADER_DEBUG
    if (uniformLocations.find(name) == uniformLocations.end())
    {
        A_LOG_OUT("[DEBUG, File: astrum_gpu/shader.h, Function: setMat4x4()]: Variable " << name << " doesn't exist.");
        return;
    }
#endif

    glUniformMatrix4fv(uniformLocations.at(name), 1, GL_FALSE, matrix);
}

void Shader::setVec3(const std::string &name, float const* const vec)
{
#ifdef A_SHADER_DEBUG
    if (uniformLocations.find(name) == uniformLocations.end())
    {
        A_LOG_OUT("[DEBUG, File: astrum_gpu/shader.h, Function: set_vec3()]: Variable " << name << " doesn't exist.");
        return;
    }
#endif

    glUniform3fv(uniformLocations.at(name), 1, vec);
}

void Shader::setVec4(const std::string &name, float const* const vec)
{
#ifdef A_SHADER_DEBUG
    if (uniformLocations.find(name) == uniformLocations.end())
    {
        A_LOG_OUT("[DEBUG, File: astrum_gpu/shader.h, Function: setVec4()]: Variable " << name << " doesn't exist.");
        return;
    }
#endif

    glUniform4fv(uniformLocations.at(name), 1, vec);
}

void Shader::setListMat4x4(const std::string &name, float const* const list, unsigned int size)
{

#ifdef A_SHADER_DEBUG
    if (uniformLocations.find(name) == uniformLocations.end())
    {
        A_LOG_OUT("[DEBUG, File: astrum_gpu/shader.h, Function: setListMat4x4()]: Variable " << name << " doesn't exist.");
        return;
    }
#endif

    glUniformMatrix4fv(uniformLocations.at(name), size, GL_FALSE, list);
}