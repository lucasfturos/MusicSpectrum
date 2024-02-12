#pragma once

#include <GL/glew.h>
#include <cmath>
#include <glm/glm.hpp>
#include <vector>

class Grid {
  private:
    GLfloat width;
    GLfloat height;
    GLint num_segments;
    std::vector<glm::vec3> vertices;
    std::vector<glm::uvec3> indices;

    void generateIndices();
    void generateVertices();

  public:
    std::vector<glm::vec3> setVertices() const;
    std::vector<glm::uvec3> setIndices() const;

    Grid(GLfloat w, GLfloat h, GLint num_seg);
    ~Grid();
};
