#include "spectrum.hpp"

/*!
 * Construtor da classe Spectrum.
 *
 * - win: Ponteiro compartilhado para a janela renderizada pelo SFML.
 * - hud: Ponteiro compartilhado para a classe HUD.
 * - fft: Ponteiro compartilhado para a classe FFT.
 */
Spectrum::Spectrum(std::shared_ptr<sf::RenderWindow> win,
                   std::shared_ptr<HUD> hud,
                   std::shared_ptr<FFT<sf::Int16>> fft)
    : window(win), hud_ptr(hud), fft_ptr(fft),
      timer_ptr(std::make_unique<Timer>()),
      sample_ptr(std::make_unique<Sample>(hud)) {}

/*!
 * Executa o loop principal da aplicação, processando e renderizando a
 * forma de onda ou FFT do sinal de áudio. A função de callback `handlePlot`
 * é utilizada para tratar os dados do plot (forma de onda ou FFT).
 *
 * `handlePlot`: Função callback para processar os dados do plot (forma de onda
 * ou FFT).
 */
void Spectrum::run(
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
