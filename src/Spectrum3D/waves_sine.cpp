#include "spectrum3D.hpp"

//! Visualiza a forma de onda do sinal de áudio.
void Spectrum3D::viewWaveform() {
    float time = timer_ptr->elapsed();
    float red = sin(time) * 0.5f + 0.5f;
    float green = 0.5f;
    float blue = cos(time) * 0.5f + 0.5f;

    shader_wave_ptr->bind();
    shader_wave_ptr->setUniform4f("uColor", glm::vec4(red, green, blue, 1.0f));

    glm::mat4 view_mat_wave = view_default_mat;

    handleMouse();

    glm::mat4 mvp = proj_mat * view_mat_wave * view_wave_mat;

    float angle = time * glm::radians(90.0f);
    glm::mat4 rotationMatrix =
        glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 1.0f, 0.0f));

    mvp *= rotationMatrix;

    shader_wave_ptr->setUniformMat4f("uMVP", mvp);

    std::vector<GLuint> indices = mobius_ptr->genIndices();
    std::vector<glm::vec3> vertices = mobius_ptr->genVertices();

    for (std::size_t i = 0; i < vertices.size(); ++i) {
        sf::Int16 sample_value = hud_ptr->sample_buffer[i % buffer_size];
        GLfloat amplitude =
            std::abs(static_cast<float>(sample_value)) / 32767.f;
        GLfloat t = hud_ptr->sound_buffer.getDuration().asSeconds();

        GLfloat frequency = (t != 0) ? 1 / t : 1;
        GLfloat wave_speed = 0.5f;
        GLfloat phase = wave_speed * t;
        GLfloat w = 2 * pi * frequency;

        glm::vec3 &vertex = vertices[i];
        vertex.y += (4.5f * amplitude) * std::sin(w * (vertex.x + phase));
        vertex.y += (2.0f * amplitude) * std::cos(w * (vertex.x * phase));
    }

    bindAndDraw(vao_wave, vbo_wave, ebo_wave, vertices, indices, GL_LINE_STRIP);

    shader_wave_ptr->unbind();
}

//! Visualiza a forma de onda com aplicação da FFT no sinal de áudio.
void Spectrum3D::viewWaveformFFT() {
    float time = timer_ptr->elapsed();
    float red = sin(time) * 0.5f + 0.5f;
    float green = cos(time) * 0.5f + 0.5f;
    float blue = 0.5f;

    shader_wfft_ptr->bind();
    shader_wfft_ptr->setUniform4f("uColor", glm::vec4(red, green, blue, 1.0f));

    glm::mat4 view_mat_fft = view_default_mat;

    handleMouse();

    glm::mat4 mvp = proj_mat * view_mat_fft * view_wff_mat;

    float angle = time * glm::radians(90.0f);
    glm::mat4 rotationMatrix =
        glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 1.0f, 0.0f));

    mvp *= rotationMatrix;

    shader_wfft_ptr->setUniformMat4f("uMVP", mvp);

    std::vector<GLuint> indices = plane_ptr->genIndices();
    std::vector<glm::vec3> vertices = plane_ptr->genVertices();

    for (std::size_t i = 0; i < vertices.size(); ++i) {
        sf::Int16 sample_value = hud_ptr->sample_buffer[i % buffer_size];
        GLfloat amplitude =
            std::abs(static_cast<float>(sample_value)) / 32767.f;
        GLfloat t = hud_ptr->sound_buffer.getDuration().asSeconds();

        glm::vec3 &vertex = vertices[i];
        GLfloat distance = std::sqrt(vertex.x * vertex.x + vertex.z * vertex.z);
        GLfloat frequency = (t != 0) ? 1 / t : 1;

        GLfloat current_time = t - distance;
        GLfloat w = 2 * pi * frequency;
        vertex.y = (4.5f * amplitude) * std::cos(w + current_time);
    }

    bindAndDraw(vao_fft, vbo_fft, ebo_fft, vertices, indices, GL_LINE_STRIP);

    shader_wfft_ptr->unbind();
}