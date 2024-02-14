#pragma once

#include <GL/glew.h>
#include <cmath>
#include <glm/glm.hpp>
#include <vector>

class Plane {
  private:
    GLfloat width;
    GLfloat height;
    GLint num_segments;

  public:
    std::vector<GLuint> genIndices();
    std::vector<glm::vec3> genVertices(GLfloat &amp, GLfloat &time);

    Plane(GLfloat w, GLfloat h, GLint num_seg);
    ~Plane();
};
