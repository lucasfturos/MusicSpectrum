#include "spectrum3D.hpp"

/*!
 * Construtor da classe Spectrum3D.
 *
 * - win: Ponteiro compartilhado para a janela renderizada pelo SFML.
 * - hud: Ponteiro compartilhado para a classe HUD.
 * - fft: Ponteiro compartilhado para a classe FFT.
 */
Spectrum3D::Spectrum3D(std::shared_ptr<sf::RenderWindow> win,
                       std::shared_ptr<HUD> hud,
                       std::shared_ptr<FFT<sf::Int16>> fft)
    : window(win), hud_ptr(hud), fft_ptr(fft),
      plane_ptr(std::make_shared<Plane>(20.0f, 20.0f, 20)),
      timer_ptr(std::make_shared<Timer>()),
      sample_ptr(std::make_unique<Sample>(hud)),
      proj_mat(
          glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f)),
      view_wave_mat(view_default_mat), view_wff_mat(view_default_mat) {
        
    glewExperimental = GL_TRUE;
    GLenum error = glewInit();
    if (error != GLEW_OK) {
        throw std::runtime_error(
            std::string("Error: ") +
            reinterpret_cast<const char *>(glewGetErrorString(error)));
    }

    if (!window->setActive()) {
        throw std::runtime_error("Failed to set window to active");
    }

    initOpenGL();
}

/*!
 * Atualiza o delta do movimento da roda do mouse.
 *
 * `w_delta`: Valor do delta do movimento da roda do mouse.
 */
void Spectrum3D::getWhellDelta(int w_delta) { whell_delta = w_delta; }

/*!
 * Executa o loop principal da aplicação, renderizando a forma de onda
 * ou FFT e chamando a função de callback para tratar os dados do plot.
 *
 * `handlePlot`: Função callback para processar os dados do plot (forma de onda
 * ou FFT).
 */
void Spectrum3D::run(
    std::function<void(std::vector<std::complex<float>>, std::size_t)>
        handlePlot) {
    sample_ptr->monoSample();
    std::vector<std::complex<float>> spectrum;

    if (hud_ptr->sound.getStatus() == sf::SoundSource::Playing) {
        sample_ptr->getSampleBuffer();

        std::size_t fft_size = 1;
        while (fft_size < buffer_size) {
            fft_size *= 2;
        }

        spectrum.resize(fft_size, 0);

        handlePlot(spectrum, fft_size);
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
}
