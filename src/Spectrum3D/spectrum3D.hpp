#pragma once

#include "../FFT/fft.hpp"
#include "../HUD/hud.hpp"
#include "../Object/plane.hpp"
#include "../OpenGL/shader.hpp"
#include "../Sample/sample.hpp"
#include "../Spectrum/spectrum.hpp"
#include "../Timer/timer.hpp"

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
    const glm::mat4 view_default_mat = glm::lookAt(
        glm::vec3(0.0f, 0.0f, 1.6f), glm::vec3(0.0f, 0.1f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    int whell_delta;
    glm::mat4 proj_mat;
    glm::mat4 view_wave_mat, view_wff_mat;

    std::unique_ptr<Shader> shader_wave_ptr;
    std::unique_ptr<Shader> shader_wfft_ptr;

    std::unique_ptr<Plane> plane_ptr;
    std::unique_ptr<Timer> timer_ptr;
    std::unique_ptr<Sample> sample_ptr;

    void clear();
    void initOpenGL();
    void handleMouse();

  public:
    void viewWaveform();
    void viewWaveformFFT();

    void getWhellDelta(int w_delta);

    void run(std::function<void(std::vector<std::complex<float>>, std::size_t)> handlePlot);

    Spectrum3D(std::shared_ptr<sf::RenderWindow> win, std::shared_ptr<HUD> hud,
               std::shared_ptr<Spectrum> spectrum, std::shared_ptr<FFT<sf::Int16>> fft);
    ~Spectrum3D();
};
