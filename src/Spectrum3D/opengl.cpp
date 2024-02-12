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
    std::vector<bool> view_mode = {
        hud_ptr->option == 5,
        hud_ptr->option == 6,
    };
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

            if (view_mode[0])
                view_wff_mat = glm::rotate(view_wff_mat, glm::radians(angle),
                                           glm::vec3(1.0f, 1.0f, 0.0f));
            if (view_mode[1])
                view_wave_mat = glm::rotate(view_wave_mat, glm::radians(angle),
                                            glm::vec3(1.0f, 1.0f, 0.0f));

            prev_pos = curr_pos;
        }
    } else {
        first_click = true;
    }

    std::vector<float> zoom_factor = {0.5f, 0.5f};
    if (whell_delta != 0) {
        std::vector<float> zoom_amount = {
            1.0f + zoom_factor[0] * abs(whell_delta) / 10.0f,
            1.0f + zoom_factor[1] * abs(whell_delta) / 10.0f};

        if (whell_delta > 0) {
            if (view_mode[1])
                view_wave_mat =
                    glm::scale(view_wave_mat, glm::vec3(zoom_amount[0]));
            else if (view_mode[0])
                view_wff_mat =
                    glm::scale(view_wff_mat, glm::vec3(zoom_amount[1]));
        } else if (whell_delta < 0) {
            if (view_mode[1])
                view_wave_mat =
                    glm::scale(view_wave_mat, glm::vec3(1.0f / zoom_amount[0]));
            else if (view_mode[0])
                view_wff_mat =
                    glm::scale(view_wff_mat, glm::vec3(1.0f / zoom_amount[1]));
        }
        whell_delta = 0;
    }
}
