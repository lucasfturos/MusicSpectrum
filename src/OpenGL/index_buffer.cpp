#include "index_buffer.hpp"
#include "util.hpp"

IndexBuffer::IndexBuffer(const GLuint *data, GLuint count) : m_count(count) {
    Gl_Call(glGenBuffers(1, &m_buffer_id));
    Gl_Call(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_buffer_id));
    Gl_Call(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data,
                         GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer() { Gl_Call(glDeleteBuffers(1, &m_buffer_id)); }

void IndexBuffer::bind() const {
    Gl_Call(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_buffer_id));
}

void IndexBuffer::unbind() const {
    Gl_Call(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

