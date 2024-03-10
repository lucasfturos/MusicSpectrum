#pragma once

#include <GL/glew.h>
#include <fstream>
#include <glm/glm.hpp>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

/*!
 * Estrutura auxiliar para armazenar o código fonte dos shaders vertex e
 * fragment.
 */
struct ShaderProgramSource {
    //! Código fonte do vertex shader.
    std::string vertex_src;

    //! Código fonte do fragment shader.
    std::string fragment_src;
};

/*!
 * Classe auxiliar para gerenciamento de programas de shader.
 *
 * A classe `Shader` carrega shaders de arquivos externos (vertex shader e
 * fragment shader), compila o programa e fornece métodos para ativação,
 * desativação e configuração de uniformes.
 */
class Shader {
  private:
    /*!
     * Identificador OpenGL do programa de shader.
     */
    GLuint m_buffer_id;
    /*!
     * Cache para localização de uniformes no programa de shader.
     *
     * Um mapa que armazena o nome do uniforme como chave e sua localização
     * (GLint) como valor. O cache evita consultas repetidas à OpenGL para
     * recuperar a localização de uniformes.
     */
    std::unordered_map<std::string, GLint> m_uniformLocationCache;

  public:
    Shader(const std::string &filepath);
    ~Shader();

    void bind() const;
    void unbind() const;

    // Set Uniforms
    void setUniform3f(const std::string &name, glm::vec3 value);
    void setUniform4f(const std::string &name, glm::vec4 value);
    void setUniformMat4f(const std::string &name, const glm::mat4 &matrix);

  private:
    GLuint createShader(const std::string &vertex_shader,
                        const std::string &fragment_shader);
    ShaderProgramSource parseShader(const std::string &filepath);
    GLuint compileShader(GLuint type, const std::string &source);
    GLint getUniformLocation(const std::string &name);
};
