#pragma once

#include <GL/glew.h>
#include <cmath>
#include <glm/glm.hpp>
#include <vector>

/*
 * @brief A classe Plane representa um plano retangular simples no espaço 3D.
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

    /*
     * @brief Constrói um novo objeto Plane com as dimensões e número de
     * segmentos especificados.
     *
     * @param w: A largura do plano.
     * @param h: A altura do plano.
     * @param num_seg: O número de segmentos (subdivisões) ao longo de cada lado
     * do plano.
     */
    Plane(GLfloat w, GLfloat h, GLint num_seg);

    /*
     * @brief Destroi o objeto Plane.
     *
     * Libera quaisquer recursos alocados pelo objeto Plane.
     */
    ~Plane();
};
