#include "vertex_buffer.hpp"
#include "util.hpp"

VertexBuffer::VertexBuffer(const void *data, GLuint size) {
    Gl_Call(glGenBuffers(1, &m_buffer_id));
    Gl_Call(glBindBuffer(GL_ARRAY_BUFFER, m_buffer_id));
    Gl_Call(glBufferData(GL_ARRAY_BUFFER, size * sizeof(GLfloat), data,
                         GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer() { Gl_Call(glDeleteBuffers(1, &m_buffer_id)); }

void VertexBuffer::bind() const {
    Gl_Call(glBindBuffer(GL_ARRAY_BUFFER, m_buffer_id));
}

void VertexBuffer::unbind() const { Gl_Call(glBindBuffer(GL_ARRAY_BUFFER, 0)); }
