#include "Renderer.h"
#include <iostream>

void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* func, const char* file, int32_t line)
{
    while (GLenum error = glGetError())
    {
        std::cout << "[OpenGl Error] (" << error << "): " << func <<
            " " << file << ":" << line << std::endl;
        return false;
    }
    return true;
}