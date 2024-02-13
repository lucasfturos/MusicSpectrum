#include "grid.hpp"

Grid::Grid(GLfloat w, GLfloat h, GLint num_seg)
    : width(w), height(h), num_segments(num_seg) {}

Grid::~Grid() {}

std::vector<glm::uvec3> Grid::genIndices() {
    std::vector<glm::uvec3> indices;
    for (auto i = 0; i < num_segments; ++i) {
        for (auto j = 0; j < num_segments; ++j) {
            GLint row1 = j * (num_segments + 1);
            GLint row2 = (j + 1) * (num_segments + 1);

            indices.push_back(glm::uvec3(row1 + i, row1 + i + 1, row2 + i + 1));
            indices.push_back(glm::uvec3(row1 + i, row2 + i + 1, row2 + i));
        }
    }
    return indices;
}

std::vector<glm::vec3> Grid::genVertices(GLfloat &amp, GLfloat &time) {
    std::vector<glm::vec3> vertices;
    for (auto i = 0; i <= num_segments; ++i) {
        for (auto j = 0; j <= num_segments; ++j) {
            GLfloat x = (static_cast<GLfloat>(i) / num_segments - 0.5f) * width;
            GLfloat z =
                (static_cast<GLfloat>(j) / num_segments - 0.5f) * height;

            GLfloat distance = sqrt(x * x + z * z);
            GLfloat frequency = (time != 0) ? 1 / time : 0;

            GLfloat y = amp * sin(-M_PI * distance * frequency + time);

            vertices.push_back(glm::vec3(x, y, z));
        }
    }
    return vertices;
}
