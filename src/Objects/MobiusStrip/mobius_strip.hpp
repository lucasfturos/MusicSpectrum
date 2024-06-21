#pragma once

#include <GL/glew.h>
#include <cmath>
#include <glm/glm.hpp>
#include <vector>

/*!
 * A classe MobiusStrip representa uma fita de Möbius no espaço 3D.
 *
 * Esta classe gera a forma geométrica de uma fita de Möbius com raio e número
 * de segmentos dados. Ela fornece funções para gerar índices e vértices para
 * renderizar a fita usando o OpenGL.
 */
class MobiusStrip {
  private:
    GLfloat diameter;
    GLfloat width;
    GLint num_segments;

  public:
    std::vector<GLuint> genIndices();
    std::vector<glm::vec3> genVertices();
    MobiusStrip(GLfloat radius, GLfloat width, GLint num_seg);
};