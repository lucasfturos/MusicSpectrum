#include "plane.hpp"

/*!
 * Construtor da classe Plane com as dimensões e número de
 * segmentos especificados.
 *
 * `w`: A largura do plano.
 *
 * `h`: A altura do plano.
 *
 * `num_seg`: O número de segmentos (subdivisões) ao longo de cada lado
 * do plano.
 */
Plane::Plane(GLfloat w, GLfloat h, GLint num_seg)
    : width(w), height(h), num_segments(num_seg) {}

/*!
 * Gera índices para renderizar o plano.
 *
 * Esta função gera um vetor de índices representando a ordem em que
 * os vértices devem ser renderizados para construir a geometria do plano.
 *
 * `std::vector<GLuint>`: Um vetor de índices para renderizar o plano.
 */
std::vector<GLuint> Plane::genIndices() {
    std::vector<GLuint> indices;
    indices.reserve(2 * num_segments * (num_segments + 1));
    for (GLint i = 0; i < num_segments; ++i) {
        GLint row = i * (num_segments + 1);
        for (GLint j = 0; j < num_segments; ++j) {
            indices.push_back(row + j);
        }
    }
    return indices;
}

/*!
 * Gera vértices para renderizar o plano.
 *
 * Esta função gera um vetor de vértices representando a geometria do
 * plano com base em suas dimensões e número de segmentos.
 *
 * `std::vector<glm::vec3>`: Um vetor de vértices para renderizar o
 * plano.
 */
std::vector<glm::vec3> Plane::genVertices() {
    std::vector<glm::vec3> vertices;
    vertices.reserve((num_segments + 1) * (num_segments + 1));

    GLfloat halfWidth = width / 2.0f;
    GLfloat halfHeight = height / 2.0f;

    for (GLint i = 0; i <= num_segments; ++i) {
        GLfloat t = static_cast<GLfloat>(i) / num_segments;
        GLfloat x = t * width - halfWidth;
        for (GLint j = 0; j <= num_segments; ++j) {
            GLfloat s = static_cast<GLfloat>(j) / num_segments;
            GLfloat z = s * height - halfHeight;
            vertices.emplace_back(x, 0.0f, z);
        }
    }

    return vertices;
}
