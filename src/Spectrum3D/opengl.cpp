#include "../Object/cubo.hpp"
#include "spectrum3D.hpp"

void Spectrum3D::initOpenGL() {
    Gl_Call(glViewport(0, 0, window->getSize().x, window->getSize().y));
    renderer_ptr->clear();

    Gl_Call(glEnable(GL_DEPTH_TEST));
    Gl_Call(glCullFace(GL_BACK));
    Gl_Call(glEnable(GL_BLEND));

    /* vao_ptr = std::make_unique<VertexArray>();

     vertexbuffer_ptr = std::make_unique<VertexBuffer>(Cubo::vertices.data(),
                                                       Cubo::vertices.size());

     layout_ptr = std::make_unique<VertexBufferLayout>();
     layout_ptr->push<GLfloat>(3);
     vao_ptr->addBuffer(*vertexbuffer_ptr, *layout_ptr);

     indexbuffer_ptr = std::make_unique<IndexBuffer>(Cubo::indices.data(),
                                                     Cubo::indices.size());
    */
    shader_ptr = std::make_unique<Shader>("./assets/shader/WaveSine.shader");
    shader_ptr->bind();
    shader_ptr->setUniform4f("uColor", glm::vec4(1.f, 0.f, 0.f, 1.f));
}
