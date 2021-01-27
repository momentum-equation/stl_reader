#pragma once
#include <GL/glew.h>

#define STL_SIZEOF_ARR(ARR) sizeof(ARR)/sizeof(ARR[0])

#define ASSERT(x) if (!(x)) __debugbreak();

#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__));

// clear existing errors
void GLClearError();

bool GLLogCall(const char* function, const char* file, int line);
