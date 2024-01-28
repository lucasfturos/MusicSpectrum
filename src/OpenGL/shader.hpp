#pragma once

#include <GL/glew.h>
#include <fstream>
#include <glm/glm.hpp>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

struct ShaderProgramSource {
    std::string vertex_src;
    std::string fragment_src;
};

class Shader {
  private:
    GLuint m_buffer_id;
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
