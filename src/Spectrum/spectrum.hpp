#pragma once

#include "../FFT/fft.hpp"
#include "../music_espectro.hpp"

class Spectrum {
  private:
    float volume = 0.f;
    bool isPlaying = false;

    sf::Sound sound;
    sf::SoundBuffer sound_buffer;

    std::vector<sf::Int16> sample_buffer;
    std::vector<sf::RectangleShape> rectangles;

    std::shared_ptr<FFT> fft_ptr;
    std::shared_ptr<sf::VideoMode> desktop;
    std::shared_ptr<sf::RenderWindow> window;

    void monoSample();
    void viewFormWave();
    void getSampleBuffer();
    void viewFormWaveRect();
    void toggleMusicPlayback();
    void optionKeyboard(sf::Event &event);
    void optionsPlot(int opc, std::vector<std::complex<float>> spectrum,
                     std::size_t fft_size);
    void viewFormWaveRectFFT(std::vector<std::complex<float>> &spectrum);
    void viewFormWaveFFT(const std::vector<std::complex<float>> &spectrum);

  public:
    void run(int opc);

    Spectrum(sf::Sound sound, sf::SoundBuffer sound_buffer,
             std::vector<sf::Int16> sample_buffer)
        : sound(std::move(sound)), sound_buffer(std::move(sound_buffer)),
          sample_buffer(std::move(sample_buffer)) {

        fft_ptr = std::make_shared<FFT>();
        window = std::make_shared<sf::RenderWindow>(
            sf::VideoMode(WIDTH, HEIGHT), "Music Espectro",
            sf::Style::Titlebar | sf::Style::Close);
        desktop =
            std::make_shared<sf::VideoMode>(sf::VideoMode::getDesktopMode());
    }
};
