#include "../Object/cubo.hpp"
#include "spectrum3D.hpp"

void Spectrum3D::viewWaveform() {
    sf::Time elapsedTime = clock.getElapsedTime();
    float seconds = elapsedTime.asSeconds();
    float red = sin(seconds) * 0.5f + 0.5f;
    float green = cos(seconds) * 0.5f + 0.5f;
    float blue = 0.5f;

    shader_ptr->bind();
    shader_ptr->setUniform4f("uColor", glm::vec4(red, green, blue, 1.0f));

    glm::mat4 view_mat_triangle =
        glm::lookAt(glm::vec3(0.0f, 0.0f, 0.4f), glm::vec3(0.0f, 0.0f, 0.0f),
                    glm::vec3(0.0f, 1.0f, 0.0f));

    handleMouse();

    glm::mat4 mvp = proj_mat * view_mat_triangle * view_mat;

    float angle = seconds * glm::radians(90.0f);
    glm::mat4 rotationMatrix =
        glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 1.0f, 0.0f));

    mvp = mvp * rotationMatrix;

    shader_ptr->bind();
    shader_ptr->setUniformMat4f("uMVP", mvp);

    clear();
    glBegin(GL_TRIANGLES);
    glVertex3f(-0.5, -0.5, 0.0);
    glVertex3f(0.5, -0.5, 0.0);
    glVertex3f(0.0, 0.5, 0.0);
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
        GLuint i1 = Cubo::indices[i];
        GLuint i2 = Cubo::indices[i + 1];
        GLuint i3 = Cubo::indices[i + 2];

        GLfloat v1x = Cubo::vertices[i1 * 3];
        GLfloat v1y = Cubo::vertices[i1 * 3 + 1];
        GLfloat v1z = Cubo::vertices[i1 * 3 + 2];

        GLfloat v2x = Cubo::vertices[i2 * 3];
        GLfloat v2y = Cubo::vertices[i2 * 3 + 1];
        GLfloat v2z = Cubo::vertices[i2 * 3 + 2];

        GLfloat v3x = Cubo::vertices[i3 * 3];
        GLfloat v3y = Cubo::vertices[i3 * 3 + 1];
        GLfloat v3z = Cubo::vertices[i3 * 3 + 2];

        glVertex3f(v1x, v1y, v1z);
        glVertex3f(v2x, v2y, v2z);
        glVertex3f(v3x, v3y, v3z);
    }
    glEnd();
    glFlush();
}
