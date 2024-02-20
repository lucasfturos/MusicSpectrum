#pragma once

#include "../FFT/fft.hpp"
#include "../HUD/hud.hpp"
#include "../Sample/sample.hpp"
#include <SFML/Graphics.hpp>
#include <functional>
#include <iostream>
#include <memory>

class Spectrum {
  private:
    std::shared_ptr<sf::RenderWindow> window;
    std::shared_ptr<HUD> hud_ptr;
    std::shared_ptr<FFT<sf::Int16>> fft_ptr;

  private:
    float gravity_velocity = 0.001f;
    const float gravity_acceleration = 9.81f;

    sf::Color start_color = sf::Color::Blue;
    sf::Color end_color = sf::Color::Magenta;

    sf::Clock clock;
    std::vector<sf::RectangleShape> rectangles;

    std::unique_ptr<Sample> sample_ptr;

  public:
    void run(std::function<void(std::vector<std::complex<float>>, std::size_t)>
                 handlePlot);

    void viewWaveform();
    void viewWaveformFFT();
    void viewWaveformRect();
    void viewWaveformRectFFT();

    Spectrum(std::shared_ptr<sf::RenderWindow> win, std::shared_ptr<HUD> hud,
             std::shared_ptr<FFT<sf::Int16>> fft);
};
