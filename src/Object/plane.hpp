#pragma once

#include <GL/glew.h>
#include <cmath>
#include <glm/glm.hpp>
#include <vector>

/*
 * A classe Plane representa um plano retangular simples no espaço 3D.
 *
 * Esta classe gera a geometria para um plano retangular com uma largura,
 * altura e número de segmentos dados. Ela fornece funções para gerar índices
 * e vértices para renderizar o plano usando OpenGL.
 */
class Plane {
  private:
    GLfloat width;
    GLfloat height;
    GLint num_segments;

  public:
    std::vector<GLuint> genIndices();
    std::vector<glm::vec3> genVertices();

    Plane(GLfloat w, GLfloat h, GLint num_seg);
    ~Plane();
};
