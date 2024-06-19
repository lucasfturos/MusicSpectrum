#include "spectrum3D.hpp"
#include <glm/gtc/type_ptr.hpp>

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

    std::vector<GLuint> indices = plane_ptr->genIndices();
    std::vector<glm::vec3> vertices = plane_ptr->genVertices();

    for (std::size_t i = 0; i < indices.size(); ++i) {
        sf::Int16 sample_value = hud_ptr->sample_buffer[i % buffer_size];
        GLfloat amplitude = static_cast<float>(sample_value) / 32767.f;
        GLfloat t = hud_ptr->sound_buffer.getDuration().asSeconds();

        glm::vec3 vertex = vertices[indices[i]];
        GLfloat distance = sqrt(vertex.x * vertex.x + vertex.z * vertex.z);
        GLfloat frequency = (t != 0) ? 1 / t : 1;

        GLfloat current_time = t - distance;
        vertex.y =
            4.5f * amplitude * sin(-pi * distance * frequency + current_time);
        vertices[indices[i]] = vertex;
    }

    glBindBuffer(GL_ARRAY_BUFFER, vbo_wave);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(glm::vec3) * vertices.size(),
                    vertices.data());

    glBindVertexArray(vao_wave);
    glDrawArrays(GL_LINE_STRIP, 0, vertices.size());
    glBindVertexArray(0);

    shader_wave_ptr->unbind();
}

//! Visualiza a FFT do sinal de áudio.
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

    for (std::size_t i = 0; i < indices.size(); ++i) {
        sf::Int16 sample_value = hud_ptr->sample_buffer[i % buffer_size];
        GLfloat amplitude = static_cast<float>(sample_value) / 32767.f;
        GLfloat t = hud_ptr->sound_buffer.getDuration().asSeconds();

        glm::vec3 vertex = vertices[indices[i]];
        GLfloat distance = sqrt(vertex.x * vertex.x + vertex.z * vertex.z);
        GLfloat frequency = (t != 0) ? 1 / t : 1;

        GLfloat current_time = t - distance;
        GLfloat w = frequency * 2 * pi;
        vertex.y = 4.5f * amplitude * cos(w + current_time);
        vertices[indices[i]] = vertex;
    }

    glBindBuffer(GL_ARRAY_BUFFER, vbo_fft);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(glm::vec3) * vertices.size(),
                    vertices.data());

    glBindVertexArray(vao_fft);
    glDrawArrays(GL_LINE_STRIP, 0, vertices.size());
    glBindVertexArray(0);

    shader_wfft_ptr->unbind();
}