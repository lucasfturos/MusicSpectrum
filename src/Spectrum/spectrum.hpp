#pragma once

#include "../FFT/fft.hpp"

class Spectrum {
  public:
    void setOption(int newOption);
    void setFileName(std::string newFilename);

  private:
    sf::Clock clock;
    sf::Clock deltaTime;
    sf::Color start_color = sf::Color::Blue;
    sf::Color end_color = sf::Color::Magenta;

    std::vector<sf::RectangleShape> rectangles;

    sf::SoundBuffer sound_buffer;
    std::vector<sf::Int16> sample_buffer;
    std::shared_ptr<FFT<sf::Int16>> fft_ptr;
    std::shared_ptr<sf::RenderWindow> window;
    int option = 3;
    std::string filename;

    void monoSample();
    void viewFormWave();
    void viewFormWaveFFT();
    void getSampleBuffer();
    void viewFormWaveRect();
    void viewFormWaveRectFFT();
    void toggleMusicPlayback();
    void handlePlot(std::vector<std::complex<float>> spectrum,
                    std::size_t fft_size);

  public:
    sf::Sound sound;

    void run();

    Spectrum(std::shared_ptr<sf::RenderWindow> win);
};
