#pragma once

#include "../FFT/fft.hpp"
#include "../HUD/hud.hpp"
#include "../Sample/sample.hpp"
#include "../Timer/timer.hpp"
#include <SFML/Graphics.hpp>
#include <functional>
#include <iostream>
#include <memory>

/*!
 * Esta classe visualiza a forma de onda de um sinal de áudio utilizando
 * retângulos coloridos. Ela também pode renderizar a FFT do sinal.
 *
 * A classe Spectrum utiliza bibliotecas como SFML e FFT para processar e
 * renderizar a forma de onda do áudio fornecido. Ela interage com outras
 * classes como HUD e Sample para auxiliar na exibição e processamento dos
 * dados.
 */
class Spectrum {
  private:
    // Variáveis privadas do constructor
    std::shared_ptr<sf::RenderWindow> window;
    std::shared_ptr<HUD> hud_ptr;
    std::shared_ptr<FFT<sf::Int16>> fft_ptr;

    std::unique_ptr<Timer> timer_ptr;
    std::unique_ptr<Sample> sample_ptr;

  private:
    float gravity_velocity = 0.001f;
    const float gravity_acceleration = 9.81f;

    sf::Color start_color = sf::Color::Blue;
    sf::Color end_color = sf::Color::Magenta;

    std::vector<sf::RectangleShape> rectangles;

  public:
    void run(std::function<void(std::vector<Float_Complex>, std::size_t)>
                 handlePlot);

    void viewWaveform();
    void viewWaveformFFT();
    void viewWaveformRect();
    void viewWaveformRectFFT();

    Spectrum(std::shared_ptr<sf::RenderWindow> win, std::shared_ptr<HUD> hud,
             std::shared_ptr<FFT<sf::Int16>> fft);
};
