#pragma once

#include <GL/glew.h>
#include <cmath>
#include <glm/glm.hpp>
#include <vector>

class Cylinder {
  private:
    GLfloat height;
    GLfloat radius_top;
    GLfloat radius_bottom;
    GLint num_segments;
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> indices;

    void generateIndices();
    void generateVertices();

  public:
    std::vector<glm::vec3> setIndices() const;
    std::vector<glm::vec3> setVertices() const;

    Cylinder(GLfloat h, GLfloat r_top, GLfloat r_bottom, GLint num_seg);
    ~Cylinder();
};
