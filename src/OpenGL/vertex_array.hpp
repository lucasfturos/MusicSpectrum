#pragma once

#include "vertex_buffer.hpp"

class VertexBufferLayout;

class VertexArray {
  private:
    GLuint m_buffer_id;

  public:
    VertexArray();
    ~VertexArray();

    void addBuffer(const VertexBuffer &vb, const VertexBufferLayout &layout);
    void bind() const;
    void unbind() const;
};
