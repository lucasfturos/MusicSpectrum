#include "spectrum3D.hpp"

//! Limpa a tela.
void Spectrum3D::clear() {
    glViewport(0, 0, window->getSize().x, window->getSize().y);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

/*!
 * Realiza a inicialização do OpenGL:
 * - Limpa o buffer de tela e define as configurações de profundidade e mistura.
 * - Carrega shaders para as formas de onda e FFT.
 * - Configura os buffers para desenho das geometrias.
 */
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

    setupBuffers(vao_wave, vbo_wave, ebo_wave);
    setupBuffers(vao_fft, vbo_fft, ebo_fft);
}

/*!
 * Configuração inicial dos buffers:
 * `vao`: ID do Vertex Array Object (VAO) ao qual os buffers serão ligados.
 * `vbo`: ID do Vertex Buffer Object (VBO) contendo os vértices a serem
 * desenhados.
 * `ebo`: ID do Element Buffer Object (EBO) contendo os índices de
 * vértices a serem desenhados.
 */
void Spectrum3D::setupBuffers(GLuint &vao, GLuint &vbo, GLuint &ebo) {
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(glm::vec3) * plane_ptr->genVertices().size(), nullptr,
                 GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3),
                          (void *)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

/*!
 * Liga o buffer de vértices e o buffer de elementos (EBO) ao VAO especificado,
 * e desenha a geometria utilizando o modo de desenho especificado.
 *
 * `vao`: ID do Vertex Array Object (VAO) ao qual os buffers serão ligados.
 * `vbo`: ID do Vertex Buffer Object (VBO) contendo os vértices a serem
 * desenhados. `vertices`: Vetor contendo os vértices a serem carregados no VBO.
 * `ebo`: ID do Element Buffer Object (EBO) contendo os índices de vértices a
 * serem desenhados. `indices`: Vetor contendo os índices que especificam a
 * ordem dos vértices. `mode`: Modo de desenho OpenGL (por exemplo,
 * GL_TRIANGLES, GL_LINES, GL_POINTS).
 */
void Spectrum3D::bindAndDraw(GLuint vao, GLuint vbo, GLuint ebo,
                             std::vector<glm::vec3> &vertices,
                             std::vector<GLuint> &indices, GLenum mode) {
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(glm::vec3) * vertices.size(),
                    vertices.data());

    glBindVertexArray(vao);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(),
                 indices.data(), GL_STATIC_DRAW);

    glDrawElements(mode, indices.size(), GL_UNSIGNED_INT, 0);

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
