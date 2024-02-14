#include "plane.hpp"

Plane::Plane(GLfloat w, GLfloat h, GLint num_seg)
    : width(w), height(h), num_segments(num_seg) {}

Plane::~Plane() {}

std::vector<GLuint> Plane::genIndices() {
    std::vector<GLuint> indices;
    for (auto i = 0; i < num_segments; ++i) {
        for (auto j = 0; j < num_segments; ++j) {
            // Mesh
            // GLint row = (j + 1) * (num_segments + 1);
            // indices.push_back(row + i + 1);
            // indices.push_back(row + i);
            // Lines
            GLint row = j * (num_segments + 1);
            indices.push_back(row + i);
        }
    }
    return indices;
}

std::vector<glm::vec3> Plane::genVertices(GLfloat &amp, GLfloat &time) {
    std::vector<glm::vec3> vertices;
    for (auto i = 0; i <= num_segments; ++i) {
        for (auto j = 0; j <= num_segments; ++j) {
            GLfloat t = static_cast<GLfloat>(i) / num_segments;
            GLfloat s = static_cast<GLfloat>(j) / num_segments;

            GLfloat x = (t - 0.5f) * width;
            GLfloat z = (s - 0.5f) * height;

            GLfloat distance = sqrt(x * x + z * z);
            GLfloat frequency = (time != 0) ? 1 / time : 0;

            GLfloat y = amp * sin(-M_PI * distance * frequency + time);

            vertices.push_back(glm::vec3(x, y, z));
        }
    }
    return vertices;
}
