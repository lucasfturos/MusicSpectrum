#pragma once

#include "../FFT/fft.hpp"
#include "../HUD/hud.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

class Spectrum {
  private:
    float gravity_velocity = 0.001f;
    const float gravity_acceleration = 9.81f;

    sf::Color start_color = sf::Color::Blue;
    sf::Color end_color = sf::Color::Magenta;

    sf::Clock clock;
    std::shared_ptr<sf::VideoMode> desktop;
    std::shared_ptr<sf::RenderWindow> window;
    std::vector<sf::RectangleShape> rectangles;

    std::shared_ptr<HUD> hud_ptr;
    std::shared_ptr<FFT<sf::Int16>> fft_ptr;

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
    void run();
    Spectrum();
};
