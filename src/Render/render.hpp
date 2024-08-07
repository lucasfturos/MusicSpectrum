#pragma once

#include "../FFT/fft.hpp"
#include "../HUD/hud.hpp"
#include "../Spectrum/spectrum.hpp"
#include "../Spectrum3D/spectrum3D.hpp"

using namespace std::chrono;

/*!
 * Classe responsável pela renderização do programa.
 *
 * A classe Render é responsável por inicializar a janela principal, gerenciar
 * objetos como HUD, Spectrum e Spectrum3D, processar eventos, controlar a taxa
 * de quadros e realizar a renderização do espectro de áudio de acordo com a
 * opção selecionada na HUD.
 */
class Render {
  private:
    const int FPS = 60;
    const double frame_duration = 1.0 / FPS;

    sf::Clock clock;

    std::shared_ptr<sf::RenderWindow> window;
    std::shared_ptr<sf::VideoMode> desktop;

    std::shared_ptr<HUD> hud_ptr;
    std::shared_ptr<Spectrum> spectrum_ptr;
    std::shared_ptr<FFT<sf::Int16>> fft_ptr;
    std::shared_ptr<Spectrum3D> spectrum3D_ptr;

    void handlePlot(std::vector<Float_Complex> spectrum,
                    std::size_t fft_size);
    void frameRate(time_point<high_resolution_clock> &prev_time);

  public:
    void run();
    Render();
    ~Render();
};
