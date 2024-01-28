#pragma once

#include "../FFT/fft.hpp"
#include "../HUD/hud.hpp"
#include "../Spectrum/spectrum.hpp"

#include "../OpenGL/renderer.hpp"
#include "../OpenGL/vertex_buffer_layout.hpp"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Spectrum3D {
  private:
    std::shared_ptr<sf::RenderWindow> window;

    std::shared_ptr<HUD> hud_ptr;
    std::shared_ptr<Spectrum> spectrum_ptr;
    std::shared_ptr<FFT<sf::Int16>> fft_ptr;

  private:
    glm::mat4 proj_mat, view_mat;

    std::unique_ptr<Renderer> renderer_ptr;
    std::unique_ptr<Shader> shader_ptr;
    std::unique_ptr<VertexArray> vao_ptr;
    std::unique_ptr<IndexBuffer> indexbuffer_ptr;
    std::unique_ptr<VertexBuffer> vertexbuffer_ptr;
    std::unique_ptr<VertexBufferLayout> layout_ptr;

    void initOpenGL();

  public:
    void viewWaveform();
    void viewWaveformFFT();

    void run(std::function<void(std::vector<std::complex<float>>, std::size_t)>
                 handlePlot);

    Spectrum3D(std::shared_ptr<sf::RenderWindow> win, std::shared_ptr<HUD> hud,
               std::shared_ptr<Spectrum> spectrum,
               std::shared_ptr<FFT<sf::Int16>> fft);
    ~Spectrum3D();
};
