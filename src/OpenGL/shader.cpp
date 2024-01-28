#include "shader.hpp"
#include "util.hpp"

Shader::Shader(const std::string &filepath) : m_buffer_id(0) {
    ShaderProgramSource source = parseShader(filepath);
    m_buffer_id = createShader(source.vertex_src, source.fragment_src);
}

Shader::~Shader() { Gl_Call(glDeleteProgram(m_buffer_id)); }

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

void Shader::bind() const { Gl_Call(glUseProgram(m_buffer_id)); }

void Shader::unbind() const { Gl_Call(glUseProgram(0)); }

void Shader::setUniform3f(const std::string &name, glm::vec3 value) {
    GLint location = getUniformLocation(name);
    Gl_Call(glUniform3f(location, value.x, value.y, value.z));
}

void Shader::setUniform4f(const std::string &name, glm::vec4 value) {
    GLint location = getUniformLocation(name);
    Gl_Call(glUniform4f(location, value.x, value.y, value.z, value.w));
}

void Shader::setUniformMat4f(const std::string &name, const glm::mat4 &matrix) {
    GLint location = getUniformLocation(name);
    Gl_Call(glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]));
}

GLint Shader::getUniformLocation(const std::string &name) {
    if (m_uniformLocationCache.find(name) != m_uniformLocationCache.end()) {
        return m_uniformLocationCache[name];
    }

    Gl_Call(GLint location = glGetUniformLocation(m_buffer_id, name.c_str()));
    if (location == -1) {
        std::cerr << "Warning: Uniform '" << name << "' doesn't exit!\n";
    }

    m_uniformLocationCache[name] = location;
    return location;
}
