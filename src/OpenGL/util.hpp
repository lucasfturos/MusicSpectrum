#pragma once

#include <GL/glew.h>
#include <iostream>

#define Gl_Call(x)  \
    GlClearError(); \
    x;              \
    ASSERT(GlLogCall(#x, __FILE__, __LINE__));

inline auto ASSERT = [](bool x) -> void {
    if (!x) {
        std::exit(EXIT_FAILURE);
    }
};

inline auto GlClearError = []() -> void {
    while (glGetError() != GL_NO_ERROR)
        ;
};

inline auto GlLogCall = [](const char *func, const char *file,
                           int line) -> bool {
    while (GLenum error = glGetError()) {
        std::cerr << "[OpenGL Error] (" << error << "):\n"
                  << "Function: " << func << '\n'
                  << "File: " << file << '\n'
                  << "Line: " << line << '\n';
        return false;
    }
    return true;
};
