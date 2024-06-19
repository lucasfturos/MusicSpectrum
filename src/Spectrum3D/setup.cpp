#include "spectrum3D.hpp"

//! Limpa a tela.
void Spectrum3D::clear() {
    glViewport(0, 0, window->getSize().x, window->getSize().y);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

//! Inicializa o OpenGL.
void Spectrum3D::initOpenGL() {
    clear();

    glEnable(GL_DEPTH_TEST);
    glCullFace(GL_BACK);
    glEnable(GL_BLEND);

    glMatrixMode(GL_PROJECTION);

    shader_wave_ptr =
        std::make_shared<Shader>("./assets/shader/WaveSine.shader");
    shader_wfft_ptr =
        std::make_shared<Shader>("./assets/shader/WaveSineFFT.shader");

    setupBuffers(vao_wave, vbo_wave);
    setupBuffers(vao_fft, vbo_fft);
}

void Spectrum3D::setupBuffers(GLuint &vao, GLuint &vbo) {
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(glm::vec3) * plane_ptr->genVertices().size(), nullptr,
                 GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3),
                          (void *)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

//! Trata o movimento do mouse.
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

            if (view_mode[0]) {
                view_wff_mat = glm::rotate(view_wff_mat, glm::radians(angle),
                                           glm::vec3(1.0f, 1.0f, 0.0f));
            }
            if (view_mode[1]) {
                view_wave_mat = glm::rotate(view_wave_mat, glm::radians(angle),
                                            glm::vec3(1.0f, 1.0f, 0.0f));
            }

            prev_pos = curr_pos;
        }
    } else {
        first_click = true;
    }

    std::vector<float> zoom_factor = {0.5f, 0.5f};
    if (whell_delta != 0) {
        std::vector<float> zoom_amount = {
            1.0f + zoom_factor[0] * abs(whell_delta) / 10.0f,
            1.0f + zoom_factor[1] * abs(whell_delta) / 10.0f,
        };

        if (whell_delta > 0) {
            if (view_mode[1]) {
                view_wave_mat =
                    glm::scale(view_wave_mat, glm::vec3(zoom_amount[0]));
            } else if (view_mode[0]) {
                view_wff_mat =
                    glm::scale(view_wff_mat, glm::vec3(zoom_amount[1]));
            }
        } else if (whell_delta < 0) {
            if (view_mode[1]) {
                view_wave_mat =
                    glm::scale(view_wave_mat, glm::vec3(1.0f / zoom_amount[0]));
            } else if (view_mode[0]) {
                view_wff_mat =
                    glm::scale(view_wff_mat, glm::vec3(1.0f / zoom_amount[1]));
            }
        }
        whell_delta = 0;
    }
}
