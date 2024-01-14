#pragma once

#include "../FFT/fft.hpp"

class Spectrum {
  private:
    int option;
    std::string filename;

    sf::Color start_color = sf::Color::Blue;
    sf::Color end_color = sf::Color::Magenta;

    sf::Clock clock;
    sf::SoundBuffer sound_buffer;
    std::vector<sf::Int16> sample_buffer;
    std::shared_ptr<FFT<sf::Int16>> fft_ptr;
    std::shared_ptr<sf::RenderWindow> window;
    std::vector<sf::RectangleShape> rectangles;

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

    void setOption(int newOption);
    void setFileName(std::string newFilename);

    void run();

    Spectrum(std::shared_ptr<sf::RenderWindow> win);
};
