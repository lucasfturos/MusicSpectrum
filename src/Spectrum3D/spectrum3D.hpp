#pragma once

#include "../FFT/fft.hpp"
#include "../HUD/hud.hpp"
#include "../Object/cylinder.hpp"
#include "../OpenGL/shader.hpp"
#include "../Spectrum/spectrum.hpp"

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
    sf::Clock clock;
    glm::mat4 proj_mat, view_mat;

    std::unique_ptr<Shader> shader_ptr;
    std::unique_ptr<Cylinder> cylinder_ptr;

    void clear();
    void initOpenGL();
    void handleMouse();

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
