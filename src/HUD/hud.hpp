#pragma once

#include "../Spectrum/spectrum.hpp"
#include "../util.hpp"

class HUD {
  private:
    int fftMode = 0;
    int spectrumMode = 0;

    sf::Clock clock;
    std::shared_ptr<sf::RenderWindow> window;

    std::shared_ptr<Spectrum> spectrum_ptr;

    void openFileDialog();
    void modeAudio();
    void styleWidget();
    void controlAudio();

  public:
    int option;
    float volume = 10.f;
    std::string filename;
    bool isPlaying = false;

    void run();

    HUD(std::shared_ptr<sf::RenderWindow> win);
    ~HUD();
};
