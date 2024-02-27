#include "spectrum.hpp"
#include <chrono>
#include <thread>

Spectrum::Spectrum(std::shared_ptr<sf::RenderWindow> win,
                   std::shared_ptr<HUD> hud,
                   std::shared_ptr<FFT<sf::Int16>> fft)
    : window(win), hud_ptr(hud), fft_ptr(fft) {
    sample_ptr = std::make_unique<Sample>(hud);
}

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
