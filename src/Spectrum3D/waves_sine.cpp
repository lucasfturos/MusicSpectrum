#include "../Object/cubo.hpp"
#include "spectrum3D.hpp"
#include <glm/gtc/type_ptr.hpp>

void Spectrum3D::viewWaveform() {
    sf::Time elapsedTime = clock.getElapsedTime();
    float seconds = elapsedTime.asSeconds();
    float red = sin(seconds) * 0.5f + 0.5f;
    float green = cos(seconds) * 0.5f + 0.5f;
    float blue = 0.5f;

    shader_ptr->bind();
    shader_ptr->setUniform4f("uColor", glm::vec4(red, green, blue, 1.0f));

    glm::mat4 view_mat_string =
        glm::lookAt(glm::vec3(0.0f, 0.0f, 10.0f), glm::vec3(0.0f, 0.1f, 0.0f),
                    glm::vec3(0.0f, 1.0f, 0.0f));

    handleMouse();

    glm::mat4 mvp = proj_mat * view_mat_string * view_mat;

    float angle = seconds * glm::radians(90.0f);
    glm::mat4 rotationMatrix =
        glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 1.0f, 0.0f));

    mvp *= rotationMatrix;

    shader_ptr->bind();
    shader_ptr->setUniformMat4f("uMVP", mvp);

    clear();
    glBegin(GL_TRIANGLES);
    for (size_t i = 0; i < cylinder_ptr->setIndices().size(); ++i) {
        glm::uvec3 indices = cylinder_ptr->setIndices()[i];

        glm::vec3 v1 = cylinder_ptr->setVertices()[indices.x];
        glm::vec3 v2 = cylinder_ptr->setVertices()[indices.y];
        glm::vec3 v3 = cylinder_ptr->setVertices()[indices.z];

        glVertex3fv(glm::value_ptr(v1));
        glVertex3fv(glm::value_ptr(v2));
        glVertex3fv(glm::value_ptr(v3));
    }
    glEnd();
    glFlush();
}

void Spectrum3D::viewWaveformFFT() {
    sf::Time elapsedTime = clock.getElapsedTime();
    float seconds = elapsedTime.asSeconds();
    float red = sin(seconds) * 0.5f + 0.5f;
    float green = cos(seconds) * 0.5f + 0.5f;
    float blue = 0.5f;

    shader_ptr->bind();
    shader_ptr->setUniform4f("uColor", glm::vec4(red, green, blue, 1.0f));

    glm::mat4 view_mat_cubo =
        glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.1f, 0.0f),
                    glm::vec3(0.0f, 1.0f, 0.0f));

    handleMouse();

    glm::mat4 mvp = proj_mat * view_mat_cubo * view_mat;

    float angle = seconds * glm::radians(90.0f);
    glm::mat4 rotationMatrix =
        glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 1.0f, 0.0f));

    mvp = mvp * rotationMatrix;

    shader_ptr->bind();
    shader_ptr->setUniformMat4f("uMVP", mvp);

    clear();
    glBegin(GL_TRIANGLES);
    for (size_t i = 0; i < Cubo::indices.size(); i += 3) {
        glm::uvec3 indices(Cubo::indices[i], Cubo::indices[i + 1],
                           Cubo::indices[i + 2]);

        glm::vec3 v1 = glm::vec3(Cubo::vertices[indices[0] * 3],
                                 Cubo::vertices[indices[0] * 3 + 1],
                                 Cubo::vertices[indices[0] * 3 + 2]);
        glm::vec3 v2 = glm::vec3(Cubo::vertices[indices[1] * 3],
                                 Cubo::vertices[indices[1] * 3 + 1],
                                 Cubo::vertices[indices[1] * 3 + 2]);
        glm::vec3 v3 = glm::vec3(Cubo::vertices[indices[2] * 3],
                                 Cubo::vertices[indices[2] * 3 + 1],
                                 Cubo::vertices[indices[2] * 3 + 2]);

        glVertex3fv(glm::value_ptr(v1));
        glVertex3fv(glm::value_ptr(v2));
        glVertex3fv(glm::value_ptr(v3));
    }
    glEnd();
    glFlush();
}
