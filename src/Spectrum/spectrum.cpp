#include "spectrum.hpp"

Spectrum::Spectrum(std::shared_ptr<sf::RenderWindow> win) : window(win) {
    fft_ptr = std::make_shared<FFT<sf::Int16>>();
    sample_buffer.reserve(buffer_size);
    if (!filename.empty()) {
        if (!sound_buffer.loadFromFile(filename)) {
            throw std::invalid_argument("Erro ao carregar a música!!");
        }
        sound.setBuffer(sound_buffer);
    }
}

void Spectrum::setOption(int newOption) { option = newOption; }

void Spectrum::setFileName(std::string newFilename) { filename = newFilename; }

void Spectrum::handlePlot(std::vector<std::complex<float>> spectrum,
                          std::size_t fft_size) {
    switch (option) {
    case 1:
        fft_ptr->fftAnalyze(sample_buffer, 1, spectrum, fft_size);
        viewFormWaveFFT();
        break;
    case 2:
        viewFormWave();
        break;
    case 3:
        fft_ptr->fftAnalyze(sample_buffer, 1, spectrum, fft_size);
        viewFormWaveRectFFT();
        break;
    case 4:
        viewFormWaveRect();
        break;
    default:
        break;
    }
}

void Spectrum::run() {
    monoSample();
    std::vector<std::complex<float>> spectrum;
    if (sound.getStatus() == sf::SoundSource::Playing) {
        getSampleBuffer();

        std::size_t fft_size = 1;
        while (fft_size < buffer_size) {
            fft_size *= 2;
        }

        spectrum.resize(fft_size, 0);

        handlePlot(spectrum, fft_size);
    }

    sf::sleep(sf::milliseconds(10));
}
