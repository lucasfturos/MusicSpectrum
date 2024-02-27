#include "plane.hpp"

// Construtor da classe Plane
Plane::Plane(GLfloat w, GLfloat h, GLint num_seg)
    : width(w), height(h), num_segments(num_seg) {}

// Destrutor da classe Plane
Plane::~Plane() {}

// Função para gerar índices para renderizar o plano
std::vector<GLuint> Plane::genIndices() {
    /*
     * @brief Gera índices para renderizar o plano.
     *
     * Esta função gera um vetor de índices representando a ordem em que
     * os vértices devem ser renderizados para construir a geometria do plano.
     *
     * @return std::vector<GLuint>: Um vetor de índices para renderizar o plano.
     */
    std::vector<GLuint> indices;
    for (auto i = 0; i < num_segments; ++i) {
        for (auto j = 0; j < num_segments; ++j) {
            // Mesh
            // GLint row = (j + 1) * (num_segments + 1);
            // indices.push_back(row + i + 1);
            // indices.push_back(row + i);
            // Lines
            GLint row = j * (num_segments + 1);
            indices.push_back(row + i);
        }
    }
    return indices;
}

// Função para gerar vértices para renderizar o plano
std::vector<glm::vec3> Plane::genVertices() {
    /*
     * @brief Gera vértices para renderizar o plano.
     *
     * Esta função gera um vetor de vértices representando a geometria do
     * plano com base em suas dimensões e número de segmentos.
     *
     * @return std::vector<glm::vec3>: Um vetor de vértices para renderizar o
     * plano.
     */
    std::vector<glm::vec3> vertices;
    for (auto i = 0; i <= num_segments; ++i) {
        for (auto j = 0; j <= num_segments; ++j) {
            GLfloat t = static_cast<GLfloat>(i) / num_segments;
            GLfloat s = static_cast<GLfloat>(j) / num_segments;

            GLfloat x = (t - 0.5f) * width;
            GLfloat y = 0.0f;
            GLfloat z = (s - 0.5f) * height;

            vertices.push_back(glm::vec3(x, y, z));
        }
    }
    return vertices;
}
