#pragma once

#include "../FFT/fft.hpp"
#include "../music_espectro.hpp"

class Spectrum {
  private:
    float volume = 0.f;
    bool isPlaying = false;

    sf::Clock clock;
    sf::Sound sound;
    sf::SoundBuffer sound_buffer;
    sf::Color start_color = sf::Color::Blue;
    sf::Color end_color = sf::Color::Magenta;

    std::vector<sf::Int16> sample_buffer;
    std::vector<sf::RectangleShape> rectangles;

    std::shared_ptr<FFT<sf::Int16>> fft_ptr;
    std::shared_ptr<sf::VideoMode> desktop;
    std::shared_ptr<sf::RenderWindow> window;

    void monoSample();
    void viewFormWave();
    void viewFormWaveFFT();
    void getSampleBuffer();
    void viewFormWaveRect();
    void viewFormWaveRectFFT();
    void toggleMusicPlayback();
    void optionKeyboard(sf::Event &event);
    void optionsPlot(int opc, std::vector<std::complex<float>> spectrum,
                     std::size_t fft_size);

  public:
    void run(int opc);

    Spectrum(sf::Sound sound, sf::SoundBuffer sound_buffer,
             std::vector<sf::Int16> sample_buffer)
        : sound(std::move(sound)), sound_buffer(std::move(sound_buffer)),
          sample_buffer(std::move(sample_buffer)) {

        fft_ptr = std::make_shared<FFT<sf::Int16>>();
        window = std::make_shared<sf::RenderWindow>(
            sf::VideoMode(WIDTH, HEIGHT), "Music Spectrum",
            sf::Style::Titlebar | sf::Style::Close);
        desktop =
            std::make_shared<sf::VideoMode>(sf::VideoMode::getDesktopMode());
    }
};
