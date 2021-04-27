#include "graphics.h"

#include "core/window/window.h"

Graphics::Graphics()
{
    A_DEBUG_LOG_OUT("[Call] Graphics constructor");
}

Graphics::~Graphics()
{
    A_DEBUG_LOG_OUT("[Call] Graphics destructor");
}

void Graphics::init()
{
    std::string v = 
    "#version 440 core\n"
    "in vec3 pos;"
    "void main()"
    "{"
    "   gl_Position = vec4(pos, 1.0);"
    "}"
    ;
    std::string f = 
    "#version 440 core\n"
    "out vec4 out_Color;"
    "void main()"
    "{"
    "   out_Color = vec4(0, 1, 0, 1);"
    "}"
    ;

    shader = std::make_unique<Shader>(v, f);

    std::vector<float> vertices
    {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };

    vao = std::make_unique<VAO>();
    vao->bind();
    vao->createAttribute(0, vertices, 3);
    vao->createIndexBuffer(std::vector<int> { 0, 1, 2 });
    vao->unbind();
}

void Graphics::update()
{
    glViewport(0, 0, Window::getWidth(), Window::getHeight());

    shader->Bind();

    vao->bind();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glDrawElements(
        GL_TRIANGLES,      
        vao->getVertexCount(),
        GL_UNSIGNED_INT,
        nullptr
    );

    vao->unbind();

    shader->Unbind();
}