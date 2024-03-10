#include "shader.hpp"
#include <iostream>

/*!
 * Construtor da classe Shader.
 *
 * Carrega os shaders a partir de um arquivo externo especificado pelo
 * caminho do arquivo, compila o programa de shader e inicializa o cache
 * de localização de uniformes.
 *
 * `filepath`: Caminho do arquivo contendo os shaders (vertex e fragment).
 */
Shader::Shader(const std::string &filepath) : m_buffer_id(0) {
    ShaderProgramSource source = parseShader(filepath);
    m_buffer_id = createShader(source.vertex_src, source.fragment_src);
}

/*!
 * Destrutor da classe Shader.
 *
 * Realiza a liberação da memória alocada pelo programa de shader em OpenGL.
 */
Shader::~Shader() { glDeleteProgram(m_buffer_id); }

/*!
 * Cria um shader individual (vertex ou fragment) a partir do código fonte.
 *
 * `type`: Tipo de shader (GL_VERTEX_SHADER ou GL_FRAGMENT_SHADER).
 *
 * `source`: Código fonte do shader.
 *
 * Retorno: Identificador OpenGL do shader criado.
 */
GLuint Shader::createShader(const std::string &vertex_shader,
                            const std::string &fragment_shader) {
    GLuint program = glCreateProgram();
    GLuint vs = compileShader(GL_VERTEX_SHADER, vertex_shader);
    GLuint fs = compileShader(GL_FRAGMENT_SHADER, fragment_shader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

/*!
 * Compila o código fonte de um shader individual.
 *
 * `type`: Tipo de shader (GL_VERTEX_SHADER ou GL_FRAGMENT_SHADER).
 *
 * `source`: Código fonte do shader.
 *
 * Returno: Identificador OpenGL do shader compilado.
 */
GLuint Shader::compileShader(GLuint type, const std::string &source) {
    GLuint id = glCreateShader(type);
    const char *src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int sucess;
    glGetShaderiv(id, GL_COMPILE_STATUS, &sucess);
    if (!sucess) {
        int len;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len);
        char *message = (char *)alloca(len * sizeof(char));
        glGetShaderInfoLog(id, len, &len, message);
        std::cerr << "Failed compile "
                  << (type == GL_VERTEX_SHADER ? "vertex" : "fragment")
                  << " shader!\n"
                  << message << '\n';
        glDeleteShader(id);
        return 0;
    }

    return id;
}

/*!
 * Carrega e separa o código fonte dos shaders (vertex e fragment) de um
 * arquivo.
 *
 * `filepath`: Caminho do arquivo contendo os shaders.
 *
 * Returno: Estrutura contendo o código fonte separado para vertex shader e
 * fragment shader.
 */
ShaderProgramSource Shader::parseShader(const std::string &filepath) {
    enum class ShaderType {
        NONE = -1,
        VERTEX = 0,
        FRAGMENT = 1,
    };

    std::string line;
    std::ifstream stream(filepath);
    std::vector<std::stringstream> ss(2);
    ShaderType type = ShaderType::NONE;
    while (getline(stream, line)) {
        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos) {
                type = ShaderType::VERTEX;
            } else if (line.find("fragment") != std::string::npos) {
                type = ShaderType::FRAGMENT;
            }
        } else {
            ss[static_cast<int>(type)] << line << '\n';
        }
    }
    return {ss[0].str(), ss[1].str()};
}

/*!
 * Ativa o programa de shader.
 *
 * Vincula o programa de shader para que ele seja usado para renderização.
 */
void Shader::bind() const { glUseProgram(m_buffer_id); }

/*!
 * Desativa o programa de shader.
 *
 * Desvincula o programa de shader, podendo ser útil para evitar interferência
 * com outros programas de shader.
 */
void Shader::unbind() const { glUseProgram(0); }

/*!
 * Define um uniforme do tipo vec3 no programa de shader.
 *
 * `name`: Nome do uniforme.
 *
 * `value`: Valor do uniforme como um vetor glm::vec3.
 */
void Shader::setUniform3f(const std::string &name, glm::vec3 value) {
    GLint location = getUniformLocation(name);
    glUniform3f(location, value.x, value.y, value.z);
}

/*!
 * Define um uniforme do tipo vec4 no programa de shader.
 *
 * `name`: Nome do uniforme.
 *
 * `value`: Valor do uniforme como um vetor glm::vec4.
 */
void Shader::setUniform4f(const std::string &name, glm::vec4 value) {
    GLint location = getUniformLocation(name);
    glUniform4f(location, value.x, value.y, value.z, value.w);
}

/*!
 * Define um uniforme do tipo mat4 no programa de shader.
 *
 * `name`: Nome do uniforme.
 *
 * `matrix`: Valor do uniforme como uma matriz glm::mat4.
 */
void Shader::setUniformMat4f(const std::string &name, const glm::mat4 &matrix) {
    GLint location = getUniformLocation(name);
    glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]);
}

/*!
 * Obtém a localização de um uniforme no programa de shader.
 *
 * Essa função verifica se a localização do uniforme já está armazenada
 * no cache `m_uniformLocationCache`. Se a localização não estiver no cache,
 * ela consulta a OpenGL e armazena o resultado no cache para consultas
 * futuras.
 *
 * `name`: Nome do uniforme.
 *
 * Returno: Localização do uniforme (GLint) ou -1 se o uniforme não for
 * encontrado.
 */
GLint Shader::getUniformLocation(const std::string &name) {
    if (m_uniformLocationCache.find(name) != m_uniformLocationCache.end()) {
        return m_uniformLocationCache[name];
    }

    GLint location = glGetUniformLocation(m_buffer_id, name.c_str());
    if (location == -1) {
        std::cerr << "Warning: Uniform '" << name << "' doesn't exit!\n";
    }

    m_uniformLocationCache[name] = location;
    return location;
}
