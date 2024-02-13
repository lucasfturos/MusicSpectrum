#include "cylinder.hpp"

Cylinder::Cylinder(GLfloat h, GLfloat r_top, GLfloat r_bottom, GLint num_seg)
    : height(h), radius_top(r_top), radius_bottom(r_bottom),
      num_segments(num_seg) {}

Cylinder::~Cylinder() {}

std::vector<glm::uvec3> Cylinder::genIndices() {
    for (auto i = 0; i < num_segments; ++i) {
        GLuint current = i * 2;
        GLuint next = (i + 1) % (num_segments + 1) * 2;

        indices.push_back(glm::uvec3(current, next, current + 1));
        indices.push_back(glm::uvec3(next + 1, current + 1, next));
    }

    const GLuint base_center_index = vertices.size() / 3;
    const GLuint top_center_index = base_center_index + num_segments + 1;

    for (auto i = 0; i < num_segments; ++i) {
        indices.push_back(
            glm::uvec3(i * 2, (i + 1) % num_segments * 2, base_center_index));
    }

    for (auto i = 0; i < num_segments; ++i) {
        indices.push_back(glm::uvec3((i + 1) % num_segments * 2 + 1, i * 2 + 1,
                                     top_center_index));
    }
    return indices;
}

std::vector<glm::vec3> Cylinder::genVertices() {
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
    return vertices;
}
