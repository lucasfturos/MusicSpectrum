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

  public:
    std::vector<glm::uvec3> genIndices();
    std::vector<glm::vec3> genVertices(GLfloat &amp, GLfloat &time);

    Grid(GLfloat w, GLfloat h, GLint num_seg);
    ~Grid();
};
