#include "spectrum3D.hpp"
#include <glm/gtc/type_ptr.hpp>

void Spectrum3D::viewWaveform() {
    sf::Time elapsedTime = clock.getElapsedTime();
    float time = elapsedTime.asSeconds();
    float red = sin(time) * 0.5f + 0.5f;
    float green = 0.5f;
    float blue = cos(time) * 0.5f + 0.5f;

    shader_wave_ptr->bind();
    shader_wave_ptr->setUniform4f("uColor", glm::vec4(red, green, blue, 1.0f));

    glm::mat4 view_mat_string =
        glm::lookAt(glm::vec3(0.0f, 0.0f, 10.0f), glm::vec3(0.0f, 0.1f, 0.0f),
                    glm::vec3(0.0f, 1.0f, 0.0f));

    handleMouse();

    glm::mat4 mvp = proj_mat * view_mat_string * view_wave_mat;

    float angle = time * glm::radians(90.0f);
    glm::mat4 rotationMatrix =
        glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 1.0f, 0.0f));

    mvp *= rotationMatrix;

    shader_wave_ptr->bind();
    shader_wave_ptr->setUniformMat4f("uMVP", mvp);

    shader_wave_ptr->unbind();
}

void Spectrum3D::viewWaveformFFT() {
    sf::Time elapsedTime = clock.getElapsedTime();
    float seconds = elapsedTime.asSeconds();
    float red = sin(seconds) * 0.5f + 0.5f;
    float green = cos(seconds) * 0.5f + 0.5f;
    float blue = 0.5f;

    shader_wfft_ptr->bind();
    shader_wfft_ptr->setUniform4f("uColor", glm::vec4(red, green, blue, 1.0f));

    glm::mat4 view_mat_cubo =
        glm::lookAt(glm::vec3(0.0f, 0.0f, 10.0f), glm::vec3(0.0f, 0.1f, 0.0f),
                    glm::vec3(0.0f, 1.0f, 0.0f));

    handleMouse();

    glm::mat4 mvp = proj_mat * view_mat_cubo * view_wff_mat;

    float angle = seconds * glm::radians(90.0f);
    glm::mat4 rotationMatrix =
        glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 1.0f, 0.0f));

    mvp *= rotationMatrix;

    shader_wfft_ptr->bind();
    shader_wfft_ptr->setUniformMat4f("uMVP", mvp);

    clear();
    glBegin(GL_LINE_STRIP);

    std::vector<GLuint> indices = plane_ptr->genIndices();
    std::vector<glm::vec3> vertices = plane_ptr->genVertices();

    for (std::size_t i = 0; i < indices.size(); ++i) {
        sf::Int16 sample_value = hud_ptr->sample_buffer[i % buffer_size];
        GLfloat amplitude = static_cast<float>(sample_value) / 32767.f;
        GLfloat t = hud_ptr->sound_buffer.getDuration().asSeconds() / 60.f;

        glm::vec3 vertex = vertices[indices[i]];
        GLfloat distance = sqrt(vertex.x * vertex.x + vertex.z * vertex.z);
        GLfloat frequency = (t != 0) ? 1 / t : 1;

        vertex.y = 4.5f * amplitude * sin(-pi * distance * frequency + t);

        glVertex3fv(glm::value_ptr(vertex));
    }

    glEnd();
    glFlush();

    shader_wfft_ptr->unbind();
}
