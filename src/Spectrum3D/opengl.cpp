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

    shader_wave_ptr =
        std::make_unique<Shader>("./assets/shader/WaveSine.shader");
    shader_wave_ptr->bind();
    shader_wave_ptr->setUniform4f("uColor", glm::vec4(1.f, 0.f, 0.f, 1.f));
    shader_wfft_ptr =
        std::make_unique<Shader>("./assets/shader/WaveSineFFT.shader");
    shader_wfft_ptr->bind();
    shader_wfft_ptr->setUniform4f("uColor", glm::vec4(0.f, 0.f, 1.f, 1.f));
}

void Spectrum3D::handleMouse() {
    static sf::Vector2i prev_pos;
    static bool first_click = true;

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        sf::Vector2i curr_pos = sf::Mouse::getPosition();
        if (first_click) {
            prev_pos = curr_pos;
            first_click = false;
        } else {
            sf::Vector2i delta = curr_pos - prev_pos;
            float angle = atan2(delta.y, delta.x);

            view_mat = glm::rotate(view_mat, glm::radians(angle),
                                   glm::vec3(1.0f, 1.0f, 0.0f));
            prev_pos = curr_pos;
        }
    } else {
        first_click = true;
    }
}
