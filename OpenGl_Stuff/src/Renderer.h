#pragma once
#include <GL/glew.h>
#include <cstdint>

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char* func, const char* file, int32_t line);