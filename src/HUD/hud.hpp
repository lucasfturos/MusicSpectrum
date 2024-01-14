#pragma once

#include "../Spectrum/spectrum.hpp"
#include "../util.hpp"

class HUD {
  private:
    int option;
    int fftMode = 0;
    int spectrumMode = 0;
    float orig_volume;

    std::shared_ptr<sf::RenderWindow> window;
    std::shared_ptr<Spectrum> spectrum_ptr;

    void modeAudio();
    void styleWidget();
    void controlAudio();
    void openFileDialog();

  public:
    sf::Sound sound;
    float volume = 10.f;
    bool isMuted = false;
    bool isPlaying = false;

    void run();

    HUD(std::shared_ptr<sf::RenderWindow> win,
        std::shared_ptr<Spectrum> spectrum);
    ~HUD();
};
