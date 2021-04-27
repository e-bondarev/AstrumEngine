#include "shader.h"

Shader::Shader(
    const std::string &vs_code,
    const std::string &fs_code,
    const str_list_t& uniform_variables,
    const str_list_t& input_variables
)
{
    handle = glCreateProgram();

    vsHandle = CreateShader(vs_code, GL_VERTEX_SHADER);
    fsHandle = CreateShader(fs_code, GL_FRAGMENT_SHADER);

    Link();

    for (int i = 0; i < uniform_variables.size(); i++)
    {
        CreateUniform(uniform_variables[i]);
    }

    for (int i = 0; i < input_variables.size(); i++)
    {
        glBindAttribLocation(handle, i, input_variables[i].c_str());
    }
}

Shader::~Shader()
{
#ifdef ASTRUM_SHADER_DEBUG

    DEBUG_LOG("Shader destructor called.");

#endif
}

void Shader::Release()
{
#ifdef ASTRUM_SHADER_DEBUG

    DEBUG_LOG("Shader freed: " << handle);

#endif

    if (handle != 0)
    {
        Unbind();
        glDetachShader(handle, vsHandle);
        glDetachShader(handle, fsHandle);
        glDeleteShader(vsHandle);
        glDeleteShader(fsHandle);
        glDeleteProgram(handle);
    }
}

void Shader::Link() const
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

unsigned int Shader::CreateShader(const std::string &shaderCode, const unsigned int &shaderType)
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

void Shader::CreateUniform(const std::string &name)
{
    const int location = glGetUniformLocation(handle, name.c_str());

    locations.insert(std::pair<std::string, int>(name.c_str(), location));
}

void Shader::SetFloat(const std::string &name, const float value)
{
#ifdef ASTRUM_SHADER_DEBUG
    if (locations.find(name) == locations.end())
    {
        A_LOG_OUT("[DEBUG, File: astrum_gpu/shader.h, Function: SetMat4x4()]: Variable " << name << " doesn't exist.");
        return;
    }
#endif

    location = locations.at(name);
    glUniform1f(location, value);
}

void Shader::SetInt(const std::string &name, const int value)
{
#ifdef ASTRUM_SHADER_DEBUG
    if (locations.find(name) == locations.end())
    {
        A_LOG_OUT("[DEBUG, File: astrum_gpu/shader.h, Function: SetMat4x4()]: Variable " << name << " doesn't exist.");
        return;
    }
#endif

    location = locations.at(name);
    glUniform1i(location, value);
}

void Shader::SetMat4x4(const std::string &name, const GLfloat *matrix)
{
#ifdef ASTRUM_SHADER_DEBUG
    if (locations.find(name) == locations.end())
    {
        A_LOG_OUT("[DEBUG, File: astrum_gpu/shader.h, Function: SetMat4x4()]: Variable " << name << " doesn't exist.");
        return;
    }
#endif

    location = locations.at(name);
    glUniformMatrix4fv(location, 1, GL_FALSE, matrix);
}

void Shader::SetVec3(const std::string &name, const GLfloat *vec)
{
#ifdef ASTRUM_SHADER_DEBUG
    if (locations.find(name) == locations.end())
    {
        A_LOG_OUT("[DEBUG, File: astrum_gpu/shader.h, Function: set_vec3()]: Variable " << name << " doesn't exist.");
        return;
    }
#endif

    location = locations.at(name);
    glUniform3fv(location, 1, vec);
}

void Shader::SetVec4(const std::string &name, const GLfloat *vec)
{
#ifdef ASTRUM_SHADER_DEBUG
    if (locations.find(name) == locations.end())
    {
        A_LOG_OUT("[DEBUG, File: astrum_gpu/shader.h, Function: SetVec4()]: Variable " << name << " doesn't exist.");
        return;
    }
#endif

    location = locations.at(name);
    glUniform4fv(location, 1, vec);
}

// MUST REMAIN.
// void operator=(const std::vector<glm::mat4x4>* list) const
// {
//     for (unsigned int i = 0; i < list->size(); i++)
//     {
//         glUniformMatrix4fv(location, list->size(), GL_FALSE, glm::value_ptr((*list)[0]));
//     }
// }

// glm::value_ptr((*list)[0]), list.size()
void Shader::SetListMat4x4(const std::string &name, const GLfloat *list, const unsigned int size)
{
#ifdef ASTRUM_SHADER_DEBUG
    if (locations.find(name) == locations.end())
    {
        A_LOG_OUT("[DEBUG, File: astrum_gpu/shader.h, Function: SetListMat4x4()]: Variable " << name << " doesn't exist.");
        return;
    }
#endif

    location = locations.at(name);

    glUniformMatrix4fv(location, size, GL_FALSE, list);
}

void Shader::SetVec4(const float x, const float y, const float z)
{
    glUniform3f(location, x, y, z);
}