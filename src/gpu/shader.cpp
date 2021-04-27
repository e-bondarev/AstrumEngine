#include "shader.h"

Shader::Shader(
    const std::string &vs_code,
    const std::string &fs_code,
    const str_list_t& uniform_variables,
    const str_list_t& input_variables
)
{
    handle = glCreateProgram();

    vsHandle = createShader(vs_code, GL_VERTEX_SHADER);
    fsHandle = createShader(fs_code, GL_FRAGMENT_SHADER);

    link();

    for (int i = 0; i < uniform_variables.size(); i++)
    {
        createUniform(uniform_variables[i]);
    }

    for (int i = 0; i < input_variables.size(); i++)
    {
        glBindAttribLocation(handle, i, input_variables[i].c_str());
    }

    A_DEBUG_LOG_OUT("[Call] Shader constructor");
}

Shader::~Shader()
{
    unbind();
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

unsigned int Shader::createShader(const std::string &shaderCode, const unsigned int &shaderType)
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

void Shader::bind()
{
    glUseProgram(handle);
}

void Shader::unbind()
{
    glUseProgram(0);
}

void Shader::createUniform(const std::string &name)
{
    const int location = glGetUniformLocation(handle, name.c_str());

    locations.insert(std::pair<std::string, int>(name.c_str(), location));
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

    location = locations.at(name);
    glUniform1f(location, value);
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

    location = locations.at(name);
    glUniform1i(location, value);
}

void Shader::setMat4x4(const std::string &name, const GLfloat *matrix)
{
#ifdef A_SHADER_DEBUG
    if (locations.find(name) == locations.end())
    {
        A_LOG_OUT("[DEBUG, File: astrum_gpu/shader.h, Function: setMat4x4()]: Variable " << name << " doesn't exist.");
        return;
    }
#endif

    location = locations.at(name);
    glUniformMatrix4fv(location, 1, GL_FALSE, matrix);
}

void Shader::setVec3(const std::string &name, const GLfloat *vec)
{
#ifdef A_SHADER_DEBUG
    if (locations.find(name) == locations.end())
    {
        A_LOG_OUT("[DEBUG, File: astrum_gpu/shader.h, Function: set_vec3()]: Variable " << name << " doesn't exist.");
        return;
    }
#endif

    location = locations.at(name);
    glUniform3fv(location, 1, vec);
}

void Shader::setVec4(const std::string &name, const GLfloat *vec)
{
#ifdef A_SHADER_DEBUG
    if (locations.find(name) == locations.end())
    {
        A_LOG_OUT("[DEBUG, File: astrum_gpu/shader.h, Function: setVec4()]: Variable " << name << " doesn't exist.");
        return;
    }
#endif

    location = locations.at(name);
    glUniform4fv(location, 1, vec);
}

void Shader::setListMat4x4(const std::string &name, const GLfloat *list, unsigned int size)
{
#ifdef A_SHADER_DEBUG
    if (locations.find(name) == locations.end())
    {
        A_LOG_OUT("[DEBUG, File: astrum_gpu/shader.h, Function: setListMat4x4()]: Variable " << name << " doesn't exist.");
        return;
    }
#endif

    location = locations.at(name);

    glUniformMatrix4fv(location, size, GL_FALSE, list);
}

void Shader::setVec4(float x, float y, float z)
{
    glUniform3f(location, x, y, z);
}