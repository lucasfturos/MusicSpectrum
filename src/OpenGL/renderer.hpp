#pragma once

#include "../OpenGL/index_buffer.hpp"
#include "../OpenGL/shader.hpp"
#include "../OpenGL/vertex_array.hpp"

class Renderer {
  public:
    void clear() const;
    void draw(const VertexArray &va, const IndexBuffer &ib,
              const Shader &shader) const;
};
