#pragma once

#include <GL/glew.h>

class IndexBuffer {
  private:
    GLuint m_buffer_id;
    GLuint m_count;

  public:
    IndexBuffer(const GLuint *data, GLuint count);
    ~IndexBuffer();

    void bind() const;
    void unbind() const;

    inline GLuint getCount() const { return m_count; }
};
