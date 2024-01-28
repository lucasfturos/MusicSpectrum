#pragma once

#include <GL/glew.h>

class VertexBuffer {
  private:
    GLuint m_buffer_id;

  public:
    VertexBuffer(const void *data, GLuint size);
    ~VertexBuffer();

    void bind() const;
    void unbind() const;
};
