#include "grid.hpp"

Grid::Grid(GLfloat w, GLfloat h, GLint num_seg)
    : width(w), height(h), num_segments(num_seg) {
    generateVertices();
    generateIndices();
}

Grid::~Grid() {}

std::vector<glm::uvec3> Grid::setIndices() const { return indices; }

std::vector<glm::vec3> Grid::setVertices() const { return vertices; }

void Grid::generateIndices() {
    for (auto i = 0; i < num_segments; ++i) {
        for (auto j = 0; j < num_segments; ++j) {
            GLint row1 = j * (num_segments + 1);
            GLint row2 = (j + 1) * (num_segments + 1);

            indices.push_back(glm::uvec3(row1 + i, row1 + i + 1, row2 + i));
            indices.push_back(glm::uvec3(row1 + i + 1, row2 + i + 1, row2 + i));
        }
    }
}

void Grid::generateVertices() {
    for (auto i = 0; i <= num_segments; ++i) {
        for (auto j = 0; j <= num_segments; ++j) {
            GLfloat x = static_cast<GLfloat>(i) / num_segments;
            GLfloat y = static_cast<GLfloat>(j) / num_segments;
            GLfloat z = 0.0f;
            vertices.push_back(glm::vec3(x, y, z));
        }
    }
}
