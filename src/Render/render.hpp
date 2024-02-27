#pragma once

#include "../FFT/fft.hpp"
#include "../HUD/hud.hpp"
#include "../Spectrum/spectrum.hpp"
#include "../Spectrum3D/spectrum3D.hpp"
#include <chrono>
#include <thread>

using namespace std::chrono;

class Render {
  private:
    const int FPS = 60;
    const double frame_duration = 1.0 / FPS;

    sf::Clock clock;

    std::shared_ptr<HUD> hud_ptr;
    std::shared_ptr<Spectrum> spectrum_ptr;
    std::shared_ptr<Spectrum3D> spectrum3D_ptr;
    std::shared_ptr<FFT<sf::Int16>> fft_ptr;

    std::shared_ptr<sf::VideoMode> desktop;
    std::shared_ptr<sf::RenderWindow> window;

    void handlePlot(std::vector<std::complex<float>> spectrum,
                    std::size_t fft_size);
    void frameRate(time_point<high_resolution_clock> &prev_time);

  public:
    void run();
    Render();
};
