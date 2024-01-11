#pragma once

#include "../FFT/fft.hpp"
#include "../HUD/hud.hpp"

class Spectrum {
  private:
    float volume = 10.f;
    bool isStop = true;
    bool isPlaying = false;

    sf::Clock clock;
    sf::Sound sound;
    sf::SoundBuffer sound_buffer;
    sf::Color start_color = sf::Color::Blue;
    sf::Color end_color = sf::Color::Magenta;

    std::vector<sf::Int16> sample_buffer;
    std::vector<sf::RectangleShape> rectangles;

    std::shared_ptr<HUD> hud_ptr;
    std::shared_ptr<FFT<sf::Int16>> fft_ptr;
    std::shared_ptr<sf::VideoMode> desktop;

    void monoSample();
    void viewFormWave();
    void viewFormWaveFFT();
    void getSampleBuffer();
    void viewFormWaveRect();
    void viewFormWaveRectFFT();
    void toggleMusicPlayback();
    void handleEvents(sf::Event &event);
    void handlePlot(int opc, std::vector<std::complex<float>> spectrum,
                    std::size_t fft_size);

  public:
    std::shared_ptr<sf::RenderWindow> window;

    void run(int opc);

    Spectrum(sf::Sound sound, sf::SoundBuffer sound_buffer,
             std::vector<sf::Int16> sample_buffer);
};
