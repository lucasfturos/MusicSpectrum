#pragma once

#include "../FFT/fft.hpp"
#include "../HUD/hud.hpp"
#include "../Plane/plane.hpp"
#include "../Sample/sample.hpp"
#include "../Shader/shader.hpp"
#include "../Timer/timer.hpp"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

/*!
 * Esta classe renderiza a forma de onda e a FFT de um sinal de áudio.
 *
 * A classe Spectrum3D utiliza bibliotecas externas como SFML, GLM e OpenGL
 * para realizar a renderização gráfica da forma de onda e da FFT de um sinal
 * de áudio fornecido. Ela também interage com outras classes como HUD,
 * Spectrum e FFT para auxiliar na exibição e processamento dos dados.
 */
class Spectrum3D {
  protected:
    const glm::mat4 view_default_mat =
        glm::lookAt(glm::vec3(0.0f, 3.0f, 12.0f), glm::vec3(0.0f, 1.5f, 0.0f),
                    glm::vec3(0.0f, 1.0f, 0.0f));

  private:
    // Variáveis privadas do constructor
    std::shared_ptr<sf::RenderWindow> window;
    std::shared_ptr<HUD> hud_ptr;
    std::shared_ptr<FFT<sf::Int16>> fft_ptr;

    std::shared_ptr<Plane> plane_ptr;
    std::shared_ptr<Timer> timer_ptr;
    std::unique_ptr<Sample> sample_ptr;

    glm::mat4 proj_mat;
    glm::mat4 view_wave_mat;
    glm::mat4 view_wff_mat;

  private:
    int whell_delta;

    GLuint vao_wave;
    GLuint vbo_wave;
    GLuint vao_fft;
    GLuint vbo_fft;

    std::shared_ptr<Shader> shader_wave_ptr;
    std::shared_ptr<Shader> shader_wfft_ptr;

    void clear();
    void initOpenGL();
    void handleMouse();
    void setupBuffers(GLuint &vao, GLuint &vbo);

  public:
    void viewWaveform();
    void viewWaveformFFT();

    void getWhellDelta(int w_delta);

    void run(std::function<void(std::vector<std::complex<float>>, std::size_t)>
                 handlePlot);

    Spectrum3D(std::shared_ptr<sf::RenderWindow> win, std::shared_ptr<HUD> hud,
               std::shared_ptr<FFT<sf::Int16>> fft);
};