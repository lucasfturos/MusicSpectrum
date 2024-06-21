#include "mobius_strip.hpp"

/*!
 * Construtor da classe MobiusStrip com as dimensões e número de
 * segmentos especificados.
 *
 * `diameter`: Diâmetro da fita.
 *
 * `width`: A largura da fita.
 *
 * `num_segments`: O número de segmentos (subdivisões) ao longo de cada lado
 * da fita.
 */
MobiusStrip::MobiusStrip(GLfloat diameter, GLfloat width, GLint num_segments)
    : diameter(diameter), width(width), num_segments(num_segments) {}

/*!
 * Gera índices para renderizar da fita de Möbius.
 *
 * Esta função gera um vetor de índices representando a ordem em que
 * os vértices devem ser renderizados para construir a geometria da fita.
 *
 * `std::vector<GLuint>`: Um vetor de índices para renderizar da fita.
 */
std::vector<GLuint> MobiusStrip::genIndices() {
    std::vector<GLuint> indices;
    indices.reserve(2 * num_segments * (num_segments + 1));
    for (GLint i = 0; i < num_segments; ++i) {
        for (GLint j = 0; j < num_segments; ++j) {
            int p0 = i * (num_segments + 1) + j;
            int p1 = p0 + 1;
            int p2 = (i + 1) * (num_segments + 1) + j;
            int p3 = p2 + 1;

            indices.push_back(p0);
            indices.push_back(p1);
            indices.push_back(p2);
            indices.push_back(p3);
        }
    }
    return indices;
}

/*!
 * Gera vértices para renderizar a fita de Möbius.
 *
 * Esta função gera um vetor de vértices representando a geometria da
 * fita com base em suas dimensões e número de segmentos.
 *
 * `std::vector<glm::vec3>`: Um vetor de vértices para renderizar o
 * fita.
 */
std::vector<glm::vec3> MobiusStrip::genVertices() {
    const double stepU = 2 * M_PI / num_segments;
    const double stepV = 2.0 / num_segments;

    std::vector<glm::vec3> vertices;
    for (int i = 0; i <= num_segments; ++i) {
        double u = i * stepU;
        double cosU = std::cos(u);
        double sinU = std::sin(u);
        for (int j = 0; j <= num_segments; ++j) {
            double v = -1.0 + j * stepV;
            double cosU2 = std::cos(u / 2.0);
            double sinU2 = std::sin(u / 2.0);
            double L = v * width;
            double x = (diameter + (L / 2.0) * cosU2) * cosU;
            double y = (L / 2.0) * sinU2;
            double z = (diameter + (L / 2.0) * cosU2) * sinU;
            vertices.push_back(glm::vec3(x, y, z));
        }
    }
    return vertices;
}
