#pragma once

#include "util.hpp"
#include <vector>

struct VertexBufferElement {
    GLuint type;
    GLuint count;
    GLubyte normalized;

    static GLuint getSizeOfType(GLuint type) {
        switch (type) {
        case GL_FLOAT:
            return 4;
        case GL_UNSIGNED_INT:
            return 4;
        case GL_UNSIGNED_BYTE:
            return 1;
        }
        ASSERT(false);
        return 0;
    }
};

class VertexBufferLayout {
  private:
    std::vector<VertexBufferElement> m_elements;
    GLuint m_stride;

  public:
    VertexBufferLayout();

    template <typename T> void push(GLuint count);

    const std::vector<VertexBufferElement> getElements() const;

    GLuint getStride() const;
};
