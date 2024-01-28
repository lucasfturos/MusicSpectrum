#include "vertex_buffer_layout.hpp"

VertexBufferLayout::VertexBufferLayout() : m_stride(0) {}

const std::vector<VertexBufferElement> VertexBufferLayout::getElements() const {
    return m_elements;
}

GLuint VertexBufferLayout::getStride() const { return m_stride; }

template <typename T> constexpr bool t_always_false() { return false; }

template <typename T> void VertexBufferLayout::push(GLuint count) {
    static_assert(t_always_false<T>(), "Type error");
}

template <> void VertexBufferLayout::push<GLfloat>(GLuint count) {
    m_elements.push_back({GL_FLOAT, count, GL_FALSE});
    m_stride += count * VertexBufferElement::getSizeOfType(GL_FLOAT);
}

template <> void VertexBufferLayout::push<GLuint>(GLuint count) {
    m_elements.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
    m_stride += count * VertexBufferElement::getSizeOfType(GL_UNSIGNED_INT);
}

template <> void VertexBufferLayout::push<GLubyte>(GLuint count) {
    m_elements.push_back({GL_UNSIGNED_BYTE, count, GL_TRUE});
    m_stride += count * VertexBufferElement::getSizeOfType(GL_UNSIGNED_BYTE);
}
