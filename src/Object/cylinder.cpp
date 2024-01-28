#include "cylinder.hpp"

Cylinder::Cylinder(GLfloat h, GLfloat r_top, GLfloat r_bottom, GLint num_seg)
    : height(h), radius_top(r_top), radius_bottom(r_bottom),
      num_segments(num_seg) {
    generateIndices();
    generateVertices();
}

Cylinder::~Cylinder() {}

std::vector<glm::vec3> Cylinder::setIndices() const { return indices; }

std::vector<glm::vec3> Cylinder::setVertices() const { return vertices; }

void Cylinder::generateIndices() {
    for (int i = 0; i < num_segments; ++i) {
        const unsigned int current = i * 2;
        const unsigned int next = (i + 1) % (num_segments + 1) * 2;

        indices.push_back(glm::vec3(current, next, current + 1));
        indices.push_back(glm::vec3(next + 1, current + 1, next));
    }
}

void Cylinder::generateVertices() {
    const GLfloat angle_increment = (2 * M_PI) / num_segments;
    for (auto i = 0; i <= num_segments; ++i) {
        GLfloat angle = i * angle_increment;

        GLfloat top_x = radius_top * cos(angle);
        GLfloat top_y = radius_top * sin(angle);
        vertices.push_back(glm::vec3(top_x, top_y, height / 2));

        GLfloat xBottom = radius_bottom * cos(angle);
        GLfloat yBottom = radius_bottom * sin(angle);
        vertices.push_back(glm::vec3(xBottom, yBottom, -height / 2));
    }
}
