#include "spectrum.hpp"

void Spectrum::optionsPlot(int opc, std::vector<std::complex<float>> spectrum,
                           std::size_t fft_size) {
    switch (opc) {
    case 1:
        fft_ptr->fftAnalyze(sample_buffer, 1, spectrum, fft_size);
        viewFormWaveFFT(spectrum);
        break;
    case 2:
        viewFormWave();
        break;
    case 3:
        fft_ptr->fftAnalyze(sample_buffer, 1, spectrum, fft_size);
        viewFormWaveRectFFT(spectrum);
        break;
    case 4:
        viewFormWaveRect();
        break;
    default:
        break;
    }
}

void Spectrum::optionKeyboard(sf::Event &event) {
    event.key.code == sf::Keyboard::Space ? toggleMusicPlayback() : (void(0));

    event.key.code == sf::Keyboard::Q ? window->close() : (void(0));

    event.key.code == sf::Keyboard::Enter ? sound.stop() : (void(0));

    if (event.key.code == sf::Keyboard::Up) {
        volume += 10.f;
        volume > 100.f ? volume = 100.f : 0;
        sound.setVolume(volume);
    }

    if (event.key.code == sf::Keyboard::Down) {
        volume -= 10.f;
        volume < .0f ? volume = 0.f : 0;
        sound.setVolume(volume);
    }
}

void Spectrum::toggleMusicPlayback() {
    if (isPlaying) {
        sound.pause();
        isPlaying = false;
    } else {
        sound.play();
        sound.setVolume(volume);
        isPlaying = true;
    }
}
