#include "../OpenGL/util.hpp"
#include "spectrum3D.hpp"

void Spectrum3D::clear() {
    Gl_Call(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void Spectrum3D::initOpenGL() {
    Gl_Call(glViewport(0, 0, window->getSize().x, window->getSize().y));
    clear();

    Gl_Call(glEnable(GL_DEPTH_TEST));
    Gl_Call(glCullFace(GL_BACK));
    Gl_Call(glEnable(GL_BLEND));

    shader_ptr = std::make_unique<Shader>("./assets/shader/WaveSine.shader");
    shader_ptr->bind();
    shader_ptr->setUniform4f("uColor", glm::vec4(1.f, 0.f, 0.f, 1.f));
}
