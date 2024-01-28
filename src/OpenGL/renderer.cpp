#include "renderer.hpp"
#include "../OpenGL/util.hpp"

void Renderer::clear() const {
    Gl_Call(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void Renderer::draw(const VertexArray &va, const IndexBuffer &ib,
                    const Shader &shader) const {
    shader.bind();
    va.bind();
    ib.bind();

    Gl_Call(
        glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr));
}
