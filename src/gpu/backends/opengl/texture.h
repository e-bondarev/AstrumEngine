#pragma once

#include <string>
#include <vector>
#include <tuple>

#include "common/opengl_object.h"
#include "common/types.h"

namespace OpenGL
{
    class Texture : public OpenGLObject
    {
    private:
        Size m_Size;

        GLint m_InternalFormat;
        GLuint m_Format;
        GLuint m_Type;

    public:
        using param_t = std::tuple<ParamType, GLuint, GLfloat>;

        Texture(Size size, unsigned char* data, GLint internalFormat, GLuint format, GLuint type, const std::vector<param_t>& parameters);
        ~Texture() override;

        void Resize(Size size);

        void SetParamFV(GLuint name, GLfloat* params);

        void Bind() const override;
        void Bind(GLuint unit) const;
        void Unbind() const override;
    };
}