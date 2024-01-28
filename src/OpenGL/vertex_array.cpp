#include "vertex_array.hpp"
#include "util.hpp"
#include "vertex_buffer_layout.hpp"

VertexArray::VertexArray() { Gl_Call(glGenVertexArrays(1, &m_buffer_id)); }

VertexArray::~VertexArray() { Gl_Call(glDeleteVertexArrays(1, &m_buffer_id)); }

void VertexArray::addBuffer(const VertexBuffer &vb,
                            const VertexBufferLayout &layout) {
    bind();
    vb.bind();
    const auto &elements = layout.getElements();
    GLuint offset = 0;
    for (GLuint i = 0; i < elements.size(); ++i) {
        const auto &element = elements[i];
        Gl_Call(glEnableVertexAttribArray(i));
        Gl_Call(glVertexAttribPointer(i, element.count, element.type,
                                      element.normalized, layout.getStride(),
                                      reinterpret_cast<const void *>(offset)));
        offset +=
            element.count * VertexBufferElement::getSizeOfType(element.type);
    }
}

void VertexArray::bind() const { Gl_Call(glBindVertexArray(m_buffer_id)); }

void VertexArray::unbind() const { Gl_Call(glBindVertexArray(0)); }
